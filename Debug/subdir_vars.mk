################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CFG_SRCS += \
../RTSCLAB4.cfg 

CMD_SRCS += \
../tm4c1294ncpdt.cmd 

C_SRCS += \
../isr.c \
../main.c \
../pinout.c \
../tm4c1294ncpdt_startup_ccs.c 

GEN_CMDS += \
./configPkg/linker.cmd 

GEN_FILES += \
./configPkg/linker.cmd \
./configPkg/compiler.opt 

GEN_MISC_DIRS += \
./configPkg 

C_DEPS += \
./isr.d \
./main.d \
./pinout.d \
./tm4c1294ncpdt_startup_ccs.d 

GEN_OPTS += \
./configPkg/compiler.opt 

OBJS += \
./isr.obj \
./main.obj \
./pinout.obj \
./tm4c1294ncpdt_startup_ccs.obj 

GEN_MISC_DIRS__QUOTED += \
"configPkg" 

OBJS__QUOTED += \
"isr.obj" \
"main.obj" \
"pinout.obj" \
"tm4c1294ncpdt_startup_ccs.obj" 

C_DEPS__QUOTED += \
"isr.d" \
"main.d" \
"pinout.d" \
"tm4c1294ncpdt_startup_ccs.d" 

GEN_FILES__QUOTED += \
"configPkg\linker.cmd" \
"configPkg\compiler.opt" 

C_SRCS__QUOTED += \
"../isr.c" \
"../main.c" \
"../pinout.c" \
"../tm4c1294ncpdt_startup_ccs.c" 


