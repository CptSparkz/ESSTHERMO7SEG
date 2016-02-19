################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Blink_Task.obj: ../Blink_Task.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/include" --include_path="C:/Users/Fsham/Desktop/7seg_output/connected_launchpad_rtos_raw/local_inc" -g --gcc --define=PART_TM4C1294NCPDT --define=ccs --define=TIVAWARE --define=ccs="ccs" --display_error_number --diag_warning=225 --diag_wrap=off --gen_func_subsections=on --preproc_with_compile --preproc_dependency="Blink_Task.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

I2Ctask.obj: ../I2Ctask.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/include" --include_path="C:/Users/Fsham/Desktop/7seg_output/connected_launchpad_rtos_raw/local_inc" -g --gcc --define=PART_TM4C1294NCPDT --define=ccs --define=TIVAWARE --define=ccs="ccs" --display_error_number --diag_warning=225 --diag_wrap=off --gen_func_subsections=on --preproc_with_compile --preproc_dependency="I2Ctask.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

StartBIOS.obj: ../StartBIOS.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/include" --include_path="C:/Users/Fsham/Desktop/7seg_output/connected_launchpad_rtos_raw/local_inc" -g --gcc --define=PART_TM4C1294NCPDT --define=ccs --define=TIVAWARE --define=ccs="ccs" --display_error_number --diag_warning=225 --diag_wrap=off --gen_func_subsections=on --preproc_with_compile --preproc_dependency="StartBIOS.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

UART_Task.obj: ../UART_Task.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/include" --include_path="C:/Users/Fsham/Desktop/7seg_output/connected_launchpad_rtos_raw/local_inc" -g --gcc --define=PART_TM4C1294NCPDT --define=ccs --define=TIVAWARE --define=ccs="ccs" --display_error_number --diag_warning=225 --diag_wrap=off --gen_func_subsections=on --preproc_with_compile --preproc_dependency="UART_Task.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/linker.cmd: ../application.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"C:/ti/xdctools_3_31_01_33_core/xs" --xdcpath="C:/ti/tirtos_tivac_2_14_00_10/packages;C:/ti/tirtos_tivac_2_14_00_10/products/bios_6_42_01_20/packages;C:/ti/tirtos_tivac_2_14_00_10/products/ndk_2_24_03_35/packages;C:/ti/tirtos_tivac_2_14_00_10/products/uia_2_00_02_39/packages;C:/ti/tirtos_tivac_2_14_00_10/products/TivaWare_C_Series-2.1.1.71b;C:/ti/ccsv6/ccs_base;" xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M4F -p ti.platforms.tiva:TM4C1294NCPDT -r release -c "C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2" "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/compiler.opt: | configPkg/linker.cmd
configPkg/: | configPkg/linker.cmd


