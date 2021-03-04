/*
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    humanoid_dongle_new.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MIMXRT1052.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"

#include "hw/bsp/board.h"
#include "tusb.h"

/* TODO: insert other definitions and declarations here. */
#define USBD_STACK_SIZE     (3*configMINIMAL_STACK_SIZE)

StackType_t usb_device_stack[USBD_STACK_SIZE];
StaticTask_t usb_device_taskdef;

#define USB_DYNAMXIEL_STACK_SZIE      (configMINIMAL_STACK_SIZE+100)
TaskHandle_t usb_dynamixel_taskdef;

static uint8_t usb_uart_itf = 0;
#define UART_USB_RX_EVENT		0b1
#define UART_USB_TX_EVENT		0b10
#define UART_TX_EVENT			0b100
#define UART_RX_EVENT			0b1000
#define UART_EVENT				UART_USB_RX_EVENT|UART_USB_TX_EVENT|UART_TX_EVENT|UART_RX_EVENT
static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
static uint32_t uart3_recevied_data;

static lpuart_handle_t uart3_handle;
static lpuart_transfer_t uart3_xfer;
static uint8_t uart3_send_buff[CFG_TUD_CDC_EP_BUFSIZE];
static uint8_t uart3_recv_buff[CFG_TUD_CDC_EP_BUFSIZE];

void uart3_transfer_callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *user_data)
{
	LPUART_GetStatusFlags(base);
    if (kStatus_LPUART_TxIdle == status)
    {
    	xTaskNotifyFromISR(usb_dynamixel_taskdef, UART_TX_EVENT, eSetBits, &xHigherPriorityTaskWoken);
    }
    else if(kStatus_LPUART_RxIdle == status || kStatus_LPUART_IdleLineDetected == status)
    {
    	if(kStatus_LPUART_IdleLineDetected == status)
    	{
    		uart3_recevied_data = CFG_TUD_CDC_EP_BUFSIZE - uart3_handle.rxDataSize;
			LPUART_TransferAbortReceive(base, &uart3_handle);
    	}
    	xTaskNotifyFromISR(usb_dynamixel_taskdef, UART_RX_EVENT, eSetBits, &xHigherPriorityTaskWoken);
    }
}

void usb_device_task(void *param) {
	(void) param;

	// This should be called after scheduler/kernel is started.
	// Otherwise it could cause kernel issue since USB IRQ handler does use RTOS queue API.
	tusb_init();

	// RTOS forever loop
	while (1) {
		// tinyusb device task
		tud_task();
	}
}

void tud_cdc_rx_cb(uint8_t itf)
{
	xTaskNotifyFromISR(usb_dynamixel_taskdef, UART_USB_RX_EVENT, eSetBits, &xHigherPriorityTaskWoken);
}

void tud_cdc_tx_complete_cb(uint8_t itf)
{
	xTaskNotifyFromISR(usb_dynamixel_taskdef, UART_USB_TX_EVENT, eSetBits, &xHigherPriorityTaskWoken);
}

void tud_cdc_line_coding_cb(uint8_t itf, cdc_line_coding_t const* p_line_coding)
{
	lpuart_config_t config =
	{
		.baudRate_Bps = p_line_coding->bit_rate,
		.parityMode = p_line_coding->parity == 1 ? kLPUART_ParityOdd : (p_line_coding->parity == 2 ? kLPUART_ParityEven : kLPUART_ParityDisabled),
		.dataBitsCount = p_line_coding->data_bits==7?kLPUART_SevenDataBits:kLPUART_EightDataBits,
		.stopBitCount = p_line_coding->stop_bits==2?kLPUART_TwoStopBit:kLPUART_OneStopBit,
		.isMsb = false,
		.txFifoWatermark = 0,
		.rxFifoWatermark = 1,
		.enableRxRTS = false,
		.enableTxCTS = false,
		.txCtsSource = kLPUART_CtsSourcePin,
		.txCtsConfig = kLPUART_CtsSampleAtStart,
		.rxIdleType = kLPUART_IdleTypeStartBit,
		.rxIdleConfig = kLPUART_IdleCharacter1,
		.enableTx = true,
		.enableRx = true
	};
	LPUART_Deinit(LPUART3);
	LPUART_Init(LPUART3, &config, LPUART3_CLOCK_SOURCE);
	LPUART3->MODIR |= (LPUART_MODIR_TXRTSE_MASK | LPUART_MODIR_TXRTSPOL_MASK);
	lpuart_transfer_t xfer =
	{
			.data = uart3_recv_buff,
			.dataSize = CFG_TUD_CDC_EP_BUFSIZE,
	};
	LPUART_TransferCreateHandle(LPUART3, &uart3_handle, uart3_transfer_callback, NULL);
	LPUART_TransferReceiveNonBlocking(LPUART3, &uart3_handle, &xfer, NULL);
//	printf("baud:%d\r\n", config.baudRate_Bps);
}

void tud_cdc_line_state_cb(uint8_t itf, bool dtr, bool rts)
{
	if(dtr && rts)
	{
	}
	else if(!dtr)
	{
	}
}

void usb_dynamixel_task(void *param) {
	uint32_t flags;
	while(1)
	{
		if(xTaskNotifyWait(pdFALSE, 0xffffffffU, &flags, portMAX_DELAY) == pdPASS)
		{
			if(flags & UART_USB_RX_EVENT)
			{
				while(uart3_handle.txDataSize)
					vTaskDelay(pdMS_TO_TICKS(1));
				uint32_t usb_recv_size = tud_cdc_n_read(usb_uart_itf, uart3_send_buff, CFG_TUD_CDC_EP_BUFSIZE);
				uart3_xfer.data     = uart3_send_buff;
				uart3_xfer.dataSize = usb_recv_size;
				LPUART_TransferSendNonBlocking(LPUART3, &uart3_handle, &uart3_xfer);
			}
			if(flags & UART_USB_TX_EVENT)
			{
				uart3_xfer.data     = uart3_recv_buff;
				uart3_xfer.dataSize = CFG_TUD_CDC_EP_BUFSIZE;
				LPUART_TransferReceiveNonBlocking(LPUART3, &uart3_handle, &uart3_xfer, NULL);
				tud_cdc_n_write_flush(usb_uart_itf);
			}
			if(flags & UART_RX_EVENT)
			{
				tud_cdc_n_write(usb_uart_itf, uart3_recv_buff, uart3_recevied_data);
				tud_cdc_n_write_flush(usb_uart_itf);
			}
			if(flags & UART_TX_EVENT)
			{
			}
		}
	}
}

/*
 * @brief   Application entry point.
 */
int main(void) {

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
#endif

	board_init();

	(void) xTaskCreateStatic(usb_device_task, "usbd", USBD_STACK_SIZE, NULL,
	configMAX_PRIORITIES - 1, usb_device_stack, &usb_device_taskdef);
	xTaskCreate(usb_dynamixel_task, "uart_task", USB_DYNAMXIEL_STACK_SZIE, NULL,
			(configMAX_PRIORITIES - 2), &usb_dynamixel_taskdef);

	vTaskStartScheduler();
	NVIC_SystemReset();
	return 0;
}
