/*
 * IRThermo.h
 *
 *  Created on: 12.02.2016
 *      Author: Philipp
 */

#ifndef LOCAL_INC_IRTHERMO_H_
#define LOCAL_INC_IRTHERMO_H_


#include <inc/hw_memmap.h>
#include <ti/drivers/GPIO.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/hal/Timer.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Mailbox.h>
#include <xdc/std.h>



void InitSPI(void);
void setup_IRThermo_Task();
void IRThermo_Task();

#endif /* LOCAL_INC_IRTHERMO_H_ */
