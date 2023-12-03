################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_bsp/board/generic_rx111/hwsetup.c 

COMPILER_OBJS += \
src/smc_gen/r_bsp/board/generic_rx111/hwsetup.obj 

C_DEPS += \
src/smc_gen/r_bsp/board/generic_rx111/hwsetup.d 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_bsp/board/generic_rx111/%.obj: ../src/smc_gen/r_bsp/board/generic_rx111/%.c 
	@echo 'Scanning and building file: $<'
	ccrx -subcommand="src\smc_gen\r_bsp\board\generic_rx111\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)" -MT="$(@:%.d=%.obj)" -MT="$(@:%.obj=%.d)" "$<"
	ccrx -subcommand="src\smc_gen\r_bsp\board\generic_rx111\cSubCommand.tmp" "$<"


