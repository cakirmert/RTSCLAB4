################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
rtos/FreeRTOS/source/portable/CCS/ARM_CM4F/%.obj: ../rtos/FreeRTOS/source/portable/CCS/ARM_CM4F/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/CCSWorkspace/RTSCLAB4" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/examples/boards/ek-tm4c1294xl" --include_path="D:/CCSWorkspace/RTSCLAB4/os" --include_path="D:/CCSWorkspace/RTSCLAB4/rtos/FreeRTOS" --include_path="D:/CCSWorkspace/RTSCLAB4/rtos/FreeRTOS/source/include" --include_path="D:/CCSWorkspace/RTSCLAB4/rtos/FreeRTOS/source/portable/CCS/ARM_CM4F" --include_path="C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --define=ccs="ccs" --define=PART_TM4C1294NCPDT -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="rtos/FreeRTOS/source/portable/CCS/ARM_CM4F/$(basename $(<F)).d_raw" --obj_directory="rtos/FreeRTOS/source/portable/CCS/ARM_CM4F" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

rtos/FreeRTOS/source/portable/CCS/ARM_CM4F/%.obj: ../rtos/FreeRTOS/source/portable/CCS/ARM_CM4F/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/CCSWorkspace/RTSCLAB4" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/examples/boards/ek-tm4c1294xl" --include_path="D:/CCSWorkspace/RTSCLAB4/os" --include_path="D:/CCSWorkspace/RTSCLAB4/rtos/FreeRTOS" --include_path="D:/CCSWorkspace/RTSCLAB4/rtos/FreeRTOS/source/include" --include_path="D:/CCSWorkspace/RTSCLAB4/rtos/FreeRTOS/source/portable/CCS/ARM_CM4F" --include_path="C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --define=ccs="ccs" --define=PART_TM4C1294NCPDT -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="rtos/FreeRTOS/source/portable/CCS/ARM_CM4F/$(basename $(<F)).d_raw" --obj_directory="rtos/FreeRTOS/source/portable/CCS/ARM_CM4F" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


