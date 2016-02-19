/*! \file Blink_Task.h
    \brief Blink task
    \author Matthias Wenzl
    \author Michael Kramer


    Blinking LED Task example.

*/

#include <stdbool.h>
#include <stdint.h>
/* Drivers Header files - fall back to driverlib for gpio*/
#include <driverlib/gpio.h>
#include <driverlib/pin_map.h>
#include <inc/hw_memmap.h>
#include <ti/sysbios/knl/Mailbox.h>


#ifndef BLINK_TASK_H_
#define BLINK_TASK_H_


typedef struct {
	uint32_t port_base;
	uint8_t led;
}led_descriptor_t;



/*! \fn BlinkFxn
 *  \brief Execute Blink Task
 *
 *
 *   \param arg0 led descriptor struct
 *   \param arg1 Ticks to wait
 *
*/
void BlinkFxn(uint32_t clock);

/*! \fn setup_Blink_Task
 *  \brief Setup Blink task
 *
 *  Setup Blink task
 *  Task has highest priority and receives 1kB of stack
 *
 *   \param led description.
 *   \param time wo wait in ticks for led to toggle
 *
 *  \return always zero. In case of error the system halts.
*/
void setup_Output_Task(uint32_t clock, Mailbox_Handle mbox1);



#endif /* UIP_TASK_H_ */
