/*
 *  ======== Blink_Task.c ========
 *  Author: Michael Kramer / Matthias Wenzl
 */
#include <stdbool.h>
#include <inc/hw_memmap.h>


/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Memory.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>


/*Board Header files */
#include <Blink_Task.h>
#include <Board.h>
#include <EK_TM4C1294XL.h>

#include <ctype.h>
#include <string.h>

#include <driverlib/gpio.h>
#include <driverlib/sysctl.h>
#include <driverlib/ssi.h>
#include <driverlib/pin_map.h>
#include <driverlib/pwm.h>
#include <driverlib/timer.h>
#include <ti/sysbios/knl/Mailbox.h>

const unsigned short chartable[43]={
    0x80, // '-'
    0x01, // '.'   Sevensegment bit order
    0x00, // '/'   (g)(f)(e)(d)(c)(a)(b)(dp)
    0x7E, // '0'
    0x0A, // '1'    _a_
    0xB6, // '2'  f|   |b
    0x9E, // '3'   |_g_|
    0xCA, // '4'  e|   |c
    0xDC, // '5'   |_d_|.dp
    0xFC, // '6'
    0x0E, // '7'
    0xFE, // '8'
    0xDE, // '9'
    0xEE, // 'A'
    0xF8, // 'B'
    0x74, // 'C'
    0xBA, // 'D'
    0xF4, // 'E'
    0xE4, // 'F'
    0x7C, // 'G'
    0xEA, // 'H'
    0x0A, // 'I'
    0x3A, // 'J'
    0x00, // 'K'
    0x70, // 'L'
    0x00, // 'M'
    0x6E, // 'N'
    0x00, // 'O'
    0xE6, // 'P'
    0xCE, // 'Q'
    0x64, // 'R'
    0xDC, // 'S'
    0xF0, // 'T'
    0x7A, // 'U'
    0x00, // 'W'
    0x00, // 'X'
    0xDA, // 'Y'
    0x00, // 'Z'
    0x00, // '['
    0x00, // '/'
    0x00, // ']'
    0x00, // '^'
    0x10, // '_'
};

Mailbox_Handle mailbox1;
void outpTask()
{
	int i, y;
	int n = 0;
	// uint32_t frequency, period, duty;
	// uint32_t sysclock = 120000000;
	int ir_thermo = 5;
	uint8_t integ[10] = {0x7E, 0x0A, 0xB6, 0x9E, 0xCA, 0xDC, 0xFC, 0x0E, 0xFE, 0xDE};
	uint16_t int_table[100];

	/* enable gpio port and SPI peripheral */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI2);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
	GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE, GPIO_PIN_2);

	/* configure alternate pins */
	GPIOPinConfigure(GPIO_PD3_SSI2CLK);
	GPIOPinConfigure(GPIO_PD0_SSI2XDAT1);
	GPIOPinConfigure(GPIO_PD1_SSI2XDAT0);
	/* user_sw1 */
	GPIOPinTypeGPIOOutput(GPIO_PORTJ_BASE, GPIO_PIN_0);

	/* configure pins for use by the SPI peripheral */
	GPIOPinTypeSSI(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3);

	/* configure clock source */
	SSIClockSourceSet(SSI2_BASE, SSI_CLOCK_SYSTEM);

	/* configure SPI and enable */
	SSIConfigSetExpClk(SSI2_BASE, 120000000, SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 10000000, 16);
	SSIEnable(SSI2_BASE);

	// timer
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
	GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, GPIO_PIN_3);
	GPIOPinConfigure(GPIO_PM3_T3CCP1);
	GPIOPinTypeTimer(GPIO_PORTM_BASE, GPIO_PIN_3);

	/*
	 timer configuration	frequency = 3800;
	period = sysclock/frequency;
	duty = period/2;
	SysCtlPeripheralEnable(TIMER3_BASE);
	TimerClockSourceSet(TIMER3_BASE, TIMER_CLOCK_SYSTEM);
	TimerConfigure(TIMER3_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PWM | TIMER_CFG_B_PWM);
	TimerControlLevel(TIMER3_BASE, TIMER_BOTH, true);
	TimerLoadSet(TIMER3_BASE, TIMER_A,  period-1);
	TimerLoadSet(TIMER3_BASE, TIMER_B, period-1);
	TimerMatchSet(TIMER3_BASE, TIMER_A, duty/8);
	TimerMatchSet(TIMER3_BASE, TIMER_A, duty/16);

	TimerEnable(TIMER3_BASE, TIMER_BOTH); */

	/* pwm configuration */
	/* SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
	SysCtlPWMClockSet(SYSCTL_PWMDIV_1);
	GPIOPinTypePWM(GPIO_PORTM_BASE, GPIO_PIN_3);
	PWMClockSet(PWM1_BASE, PWM_SYSCLK_DIV_2);
	PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);
	PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, 400);
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, 100);
	PWMGenEnable(PWM1_BASE, PWM_GEN_0);
	PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT, true); */


	/* Schleife zum erzeugen von integer array von 0 bis 99 */


	for (i=0; i<=9; i++)
	{
		for (y=0; y<=9; y++)
		{
			int_table[n] = integ[i] | integ[y] << 8;
			n++;
		}
	}
	for (;;){
			Mailbox_pend(mailbox1, &ir_thermo, BIOS_WAIT_FOREVER);
			System_printf("IRTHERMO Value: %d\n", ir_thermo);
			SSIDataPut(SSI2_BASE, int_table[ir_thermo]);
			while (SSIBusy(SSI2_BASE));
			GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_2, 0xFF);
			GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_2, 0);
	}


}

void setup_Output_Task(uint32_t clock, Mailbox_Handle mbox1)
{
	Task_Params taskOutpParams;
	Task_Handle taskOutp;
	Error_Block eb;
	/* Create Blink task with priority 15*/
	    Error_init(&eb);
	    Task_Params_init(&taskOutpParams);
	    taskOutpParams.stackSize = 512;/*stack in bytes*/
	    taskOutpParams.priority = 15;/*15 is default 16 is highest priority -> see RTOS configuration*/
	    taskOutp = Task_create((Task_FuncPtr)outpTask, &taskOutpParams, &eb);
	    if (taskOutp == NULL)
	    {
	    	System_abort("TaskUART create failed");
	    }
		mailbox1 = mbox1;
}
