################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include xip/subdir.mk
-include utilities/subdir.mk
-include usb/phy/subdir.mk
-include usb/host/class/subdir.mk
-include usb/host/subdir.mk
-include usb/device/source/ehci/subdir.mk
-include usb/device/source/subdir.mk
-include usb/device/class/video/subdir.mk
-include usb/device/class/printer/subdir.mk
-include usb/device/class/phdc/subdir.mk
-include usb/device/class/msc/subdir.mk
-include usb/device/class/hid/subdir.mk
-include usb/device/class/dfu/subdir.mk
-include usb/device/class/cdc_rndis/subdir.mk
-include usb/device/class/cdc/subdir.mk
-include usb/device/class/ccid/subdir.mk
-include usb/device/class/audio/subdir.mk
-include usb/device/class/subdir.mk
-include tinyusb_src/portable/valentyusb/eptri/subdir.mk
-include tinyusb_src/portable/ti/msp430x5xx/subdir.mk
-include tinyusb_src/portable/template/subdir.mk
-include tinyusb_src/portable/st/synopsys/subdir.mk
-include tinyusb_src/portable/st/stm32_fsdev/subdir.mk
-include tinyusb_src/portable/sony/cxd56/subdir.mk
-include tinyusb_src/portable/nxp/transdimension/subdir.mk
-include tinyusb_src/portable/nxp/lpc_ip3511/subdir.mk
-include tinyusb_src/portable/nxp/lpc18_43/subdir.mk
-include tinyusb_src/portable/nxp/lpc17_40/subdir.mk
-include tinyusb_src/portable/nuvoton/nuc505/subdir.mk
-include tinyusb_src/portable/nuvoton/nuc121/subdir.mk
-include tinyusb_src/portable/nuvoton/nuc120/subdir.mk
-include tinyusb_src/portable/nordic/nrf5x/subdir.mk
-include tinyusb_src/portable/microchip/samg/subdir.mk
-include tinyusb_src/portable/microchip/samd/subdir.mk
-include tinyusb_src/portable/espressif/esp32s2/subdir.mk
-include tinyusb_src/portable/dialog/da146xx/subdir.mk
-include tinyusb_src/host/ohci/subdir.mk
-include tinyusb_src/host/ehci/subdir.mk
-include tinyusb_src/host/subdir.mk
-include tinyusb_src/device/subdir.mk
-include tinyusb_src/common/subdir.mk
-include tinyusb_src/class/vendor/subdir.mk
-include tinyusb_src/class/usbtmc/subdir.mk
-include tinyusb_src/class/net/subdir.mk
-include tinyusb_src/class/msc/subdir.mk
-include tinyusb_src/class/midi/subdir.mk
-include tinyusb_src/class/hid/subdir.mk
-include tinyusb_src/class/dfu/subdir.mk
-include tinyusb_src/class/cdc/subdir.mk
-include tinyusb_src/class/bth/subdir.mk
-include tinyusb_src/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include freertos/freertos_kernel/portable/MemMang/subdir.mk
-include freertos/freertos_kernel/portable/GCC/ARM_CM4F/subdir.mk
-include freertos/freertos_kernel/subdir.mk
-include drivers/freertos/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include component/uart/subdir.mk
-include component/serial_manager/subdir.mk
-include component/osa/subdir.mk
-include component/lists/subdir.mk
-include board/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: humanoid_dongle_new.axf

# Tool invocations
humanoid_dongle_new.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"D:\nxp\window_workspace\humanoid_dongle_new\libs" -Xlinker -Map="humanoid_dongle_new.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -T humanoid_dongle_new_Debug.ld -o "humanoid_dongle_new.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) humanoid_dongle_new.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "humanoid_dongle_new.axf"; # arm-none-eabi-objcopy -v -O binary "humanoid_dongle_new.axf" "humanoid_dongle_new.bin" ; # checksum -p MIMXRT1052xxxxB -d "humanoid_dongle_new.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
