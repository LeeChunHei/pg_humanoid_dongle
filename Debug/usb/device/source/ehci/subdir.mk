################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../usb/device/source/ehci/usb_device_ehci.c 

OBJS += \
./usb/device/source/ehci/usb_device_ehci.o 

C_DEPS += \
./usb/device/source/ehci/usb_device_ehci.d 


# Each subdirectory must supply rules for building sources it contributes
usb/device/source/ehci/%.o: ../usb/device/source/ehci/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MIMXRT1052DVL6B -DCPU_MIMXRT1052DVL6B_cm7 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=1 -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DCFG_TUSB_MCU=OPT_MCU_MIMXRT10XX -I"D:\nxp\window_workspace\humanoid_dongle_new\board" -I"D:\nxp\window_workspace\humanoid_dongle_new\source" -I"D:\nxp\window_workspace\humanoid_dongle_new" -I"D:\nxp\window_workspace\humanoid_dongle_new\freertos\freertos_kernel\include" -I"D:\nxp\window_workspace\humanoid_dongle_new\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"D:\nxp\window_workspace\humanoid_dongle_new\drivers" -I"D:\nxp\window_workspace\humanoid_dongle_new\device" -I"D:\nxp\window_workspace\humanoid_dongle_new\CMSIS" -I"D:\nxp\window_workspace\humanoid_dongle_new\xip" -I"D:\nxp\window_workspace\humanoid_dongle_new\drivers\freertos" -I"D:\nxp\window_workspace\humanoid_dongle_new\utilities" -I"D:\nxp\window_workspace\humanoid_dongle_new\component\serial_manager" -I"D:\nxp\window_workspace\humanoid_dongle_new\component\lists" -I"D:\nxp\window_workspace\humanoid_dongle_new\component\uart" -I"D:\nxp\window_workspace\humanoid_dongle_new\usb\include" -I"D:\nxp\window_workspace\humanoid_dongle_new\component\osa" -I"D:\nxp\window_workspace\humanoid_dongle_new\usb\device\class\audio" -I"D:\nxp\window_workspace\humanoid_dongle_new\usb\device\class" -I"D:\nxp\window_workspace\humanoid_dongle_new\usb\device\source" -I"D:\nxp\window_workspace\humanoid_dongle_new\usb\device\include" -I"D:\nxp\window_workspace\humanoid_dongle_new\usb\device\source\ehci" -I"D:\nxp\window_workspace\humanoid_dongle_new\usb\phy" -I"D:\nxp\window_workspace\humanoid_dongle_new\source\generated" -I"D:\nxp\window_workspace\humanoid_dongle_new\usb\device\class\ccid" -I"D:\nxp\window_workspace\humanoid_dongle_new\usb\device\class\cdc" -I"D:\nxp\window_workspace\humanoid_dongle_new\usb\device\class\cdc_rndis" -I"D:\nxp\window_workspace\humanoid_dongle_new\usb\device\class\dfu" -I"D:\nxp\window_workspace\humanoid_dongle_new\usb\device\class\hid" -I"D:\nxp\window_workspace\humanoid_dongle_new\usb\device\class\msc" -I"D:\nxp\window_workspace\humanoid_dongle_new\usb\device\class\phdc" -I"D:\nxp\window_workspace\humanoid_dongle_new\usb\device\class\printer" -I"D:\nxp\window_workspace\humanoid_dongle_new\usb\device\class\video" -I"D:\nxp\window_workspace\humanoid_dongle_new\usb\host\class" -I"D:\nxp\window_workspace\humanoid_dongle_new\usb\host" -I"D:\nxp\window_workspace\tinyusb\src" -I"D:\nxp\window_workspace\tinyusb" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


