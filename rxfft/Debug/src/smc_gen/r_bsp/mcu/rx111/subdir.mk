################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_bsp/mcu/rx111/mcu_clocks.c \
../src/smc_gen/r_bsp/mcu/rx111/mcu_init.c \
../src/smc_gen/r_bsp/mcu/rx111/mcu_interrupts.c \
../src/smc_gen/r_bsp/mcu/rx111/vecttbl.c 

COMPILER_OBJS += \
src/smc_gen/r_bsp/mcu/rx111/mcu_clocks.obj \
src/smc_gen/r_bsp/mcu/rx111/mcu_init.obj \
src/smc_gen/r_bsp/mcu/rx111/mcu_interrupts.obj \
src/smc_gen/r_bsp/mcu/rx111/vecttbl.obj 

C_DEPS += \
src/smc_gen/r_bsp/mcu/rx111/mcu_clocks.d \
src/smc_gen/r_bsp/mcu/rx111/mcu_init.d \
src/smc_gen/r_bsp/mcu/rx111/mcu_interrupts.d \
src/smc_gen/r_bsp/mcu/rx111/vecttbl.d 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_bsp/mcu/rx111/%.obj: ../src/smc_gen/r_bsp/mcu/rx111/%.c 
	@echo 'Scanning and building file: $<'
	ccrx -subcommand="src\smc_gen\r_bsp\mcu\rx111\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)" -MT="$(@:%.d=%.obj)" -MT="$(@:%.obj=%.d)" "$<"
	ccrx -subcommand="src\smc_gen\r_bsp\mcu\rx111\cSubCommand.tmp" "$<"


