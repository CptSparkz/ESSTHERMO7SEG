/*
 * CCSv6 project using TI-RTOS
 *
 */

/*
 *  ======== StartBIOS.c ========
 */
/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Memory.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Mailbox.h>
#include <ti/sysbios/knl/Event.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/hal/Timer.h>
#include <ti/sysbios/knl/Event.h>

/* TI-RTOS Header files */
#include <ti/drivers/UART.h>


/*Board Header files */
#include <Board.h>
#include <EK_TM4C1294XL.h>

/*application header files*/
#include <ctype.h>
#include <string.h>

#include "IRThermo.h"
#include <Blink_Task.h>
#include <UART_Task.h>


Mailbox_Handle mailbox1;
void createMailbox1(void);

int main(void)
{
    uint32_t ui32SysClock;

	/* Call board init functions. */
	ui32SysClock = Board_initGeneral(120*1000*1000);
	createMailbox1();
	Board_initI2C();
	Board_initSPI();

	setup_IRThermo_Task(mailbox1);
	System_printf("Created IRThermo Task\n");

	setup_Output_Task(ui32SysClock, mailbox1);
	System_printf("Created Output Task\n");

    /* SysMin will only print to the console upon calling flush or exit */

    System_printf("Start BIOS\n");
    System_flush();

    /* Start BIOS */
    BIOS_start();
}

void createMailbox1(void)
{
	Error_Block eb;
	Mailbox_Params mailboxParams;

	Error_init(&eb);
	Mailbox_Params_init(&mailboxParams);

	mailbox1 = Mailbox_create((SizeT)10, 10, &mailboxParams, &eb);
	if (mailbox1 == NULL)
	{
		System_abort("Mailbox create failed");
	}
	System_printf("Created MailBox \n");
}


