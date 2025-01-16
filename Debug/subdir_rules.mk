################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-113458513:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-113458513-inproc

build-113458513-inproc: ../RTSCLAB4.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"C:/ti/ccs1250/xdctools_3_25_06_96/xs" --xdcpath= xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M4F -p ti.platforms.tiva:TivaTM4C1294NCPDT -r release -c "C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-113458513 ../RTSCLAB4.cfg
configPkg/compiler.opt: build-113458513
configPkg: build-113458513

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/CCSWorkspace/RTSCLAB4" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295/examples/boards/ek-tm4c1294xl" --include_path="D:/CCSWorkspace/RTSCLAB4/os" --include_path="D:/CCSWorkspace/RTSCLAB4/rtos/FreeRTOS" --include_path="D:/CCSWorkspace/RTSCLAB4/rtos/FreeRTOS/source/include" --include_path="D:/CCSWorkspace/RTSCLAB4/rtos/FreeRTOS/source/portable/CCS/ARM_CM4F" --include_path="C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --define=ccs="ccs" --define=PART_TM4C1294NCPDT -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


