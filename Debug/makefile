################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS

GEN_OPTS__FLAG := --cmd_file="configPkg/compiler.opt" 
GEN_CMDS__FLAG := -l"configPkg/linker.cmd" 

ORDERED_OBJS += \
"./isr.obj" \
"./main.obj" \
"./pinout.obj" \
"./tm4c1294ncpdt_startup_ccs.obj" \
"./rtos/FreeRTOS/source/croutine.obj" \
"./rtos/FreeRTOS/source/event_groups.obj" \
"./rtos/FreeRTOS/source/list.obj" \
"./rtos/FreeRTOS/source/queue.obj" \
"./rtos/FreeRTOS/source/stream_buffer.obj" \
"./rtos/FreeRTOS/source/tasks.obj" \
"./rtos/FreeRTOS/source/timers.obj" \
"./rtos/FreeRTOS/source/portable/CCS/ARM_CM4F/port.obj" \
"./rtos/FreeRTOS/source/portable/CCS/ARM_CM4F/portasm.obj" \
"./rtos/FreeRTOS/source/portable/MemMang/heap_1.obj" \
"../tm4c1294ncpdt.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include rtos/FreeRTOS/source/subdir_vars.mk
-include rtos/FreeRTOS/source/portable/CCS/ARM_CM4F/subdir_vars.mk
-include rtos/FreeRTOS/source/portable/MemMang/subdir_vars.mk
-include subdir_rules.mk
-include rtos/FreeRTOS/source/subdir_rules.mk
-include rtos/FreeRTOS/source/portable/CCS/ARM_CM4F/subdir_rules.mk
-include rtos/FreeRTOS/source/portable/MemMang/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
RTSCLAB4.out 

EXE_OUTPUTS__QUOTED += \
"RTSCLAB4.out" 


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "RTSCLAB4.out"

# Tool invocations
RTSCLAB4.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: Arm Linker'
	"C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --define=ccs="ccs" --define=PART_TM4C1294NCPDT -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"RTSCLAB4.map" --heap_size=0 --stack_size=512 -i"C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/lib" -i"C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="RTSCLAB4_linkInfo.xml" --rom_model -o "RTSCLAB4.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(GEN_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "isr.obj" "main.obj" "pinout.obj" "tm4c1294ncpdt_startup_ccs.obj" "rtos\FreeRTOS\source\croutine.obj" "rtos\FreeRTOS\source\event_groups.obj" "rtos\FreeRTOS\source\list.obj" "rtos\FreeRTOS\source\queue.obj" "rtos\FreeRTOS\source\stream_buffer.obj" "rtos\FreeRTOS\source\tasks.obj" "rtos\FreeRTOS\source\timers.obj" "rtos\FreeRTOS\source\portable\CCS\ARM_CM4F\port.obj" "rtos\FreeRTOS\source\portable\CCS\ARM_CM4F\portasm.obj" "rtos\FreeRTOS\source\portable\MemMang\heap_1.obj" 
	-$(RM) "isr.d" "main.d" "pinout.d" "tm4c1294ncpdt_startup_ccs.d" "rtos\FreeRTOS\source\croutine.d" "rtos\FreeRTOS\source\event_groups.d" "rtos\FreeRTOS\source\list.d" "rtos\FreeRTOS\source\queue.d" "rtos\FreeRTOS\source\stream_buffer.d" "rtos\FreeRTOS\source\tasks.d" "rtos\FreeRTOS\source\timers.d" "rtos\FreeRTOS\source\portable\CCS\ARM_CM4F\port.d" "rtos\FreeRTOS\source\portable\MemMang\heap_1.d" 
	-$(RM) "rtos\FreeRTOS\source\portable\CCS\ARM_CM4F\portasm.d" 
	-$(RMDIR) $(GEN_MISC_DIRS__QUOTED)
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

