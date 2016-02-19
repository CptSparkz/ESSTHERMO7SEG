################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
TM4C1294XL/EK_TM4C1294XL.obj: ../TM4C1294XL/EK_TM4C1294XL.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/include" --include_path="C:/Users/Fsham/Desktop/7seg_output/connected_launchpad_rtos_raw/local_inc" -g --gcc --define=PART_TM4C1294NCPDT --define=ccs --define=TIVAWARE --define=ccs="ccs" --display_error_number --diag_warning=225 --diag_wrap=off --gen_func_subsections=on --preproc_with_compile --preproc_dependency="TM4C1294XL/EK_TM4C1294XL.pp" --obj_directory="TM4C1294XL" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


