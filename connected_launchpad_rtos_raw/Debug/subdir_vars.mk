################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../EK_TM4C1294XL.cmd 

CFG_SRCS += \
../application.cfg 

C_SRCS += \
../Blink_Task.c \
../I2Ctask.c \
../StartBIOS.c \
../UART_Task.c 

OBJS += \
./Blink_Task.obj \
./I2Ctask.obj \
./StartBIOS.obj \
./UART_Task.obj 

C_DEPS += \
./Blink_Task.pp \
./I2Ctask.pp \
./StartBIOS.pp \
./UART_Task.pp 

GEN_MISC_DIRS += \
./configPkg/ 

GEN_CMDS += \
./configPkg/linker.cmd 

GEN_OPTS += \
./configPkg/compiler.opt 

GEN_FILES += \
./configPkg/linker.cmd \
./configPkg/compiler.opt 

GEN_FILES__QUOTED += \
"configPkg\linker.cmd" \
"configPkg\compiler.opt" 

GEN_MISC_DIRS__QUOTED += \
"configPkg\" 

C_DEPS__QUOTED += \
"Blink_Task.pp" \
"I2Ctask.pp" \
"StartBIOS.pp" \
"UART_Task.pp" 

OBJS__QUOTED += \
"Blink_Task.obj" \
"I2Ctask.obj" \
"StartBIOS.obj" \
"UART_Task.obj" 

C_SRCS__QUOTED += \
"../Blink_Task.c" \
"../I2Ctask.c" \
"../StartBIOS.c" \
"../UART_Task.c" 

GEN_CMDS__FLAG += \
-l"./configPkg/linker.cmd" 

GEN_OPTS__FLAG += \
--cmd_file="./configPkg/compiler.opt" 


