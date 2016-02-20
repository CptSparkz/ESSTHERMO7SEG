#include "IRThermo.h"

Mailbox_Handle mailbox1;

void InitSPI(){

	 uint32_t ui32SysClock;
	/* Call board init functions. */
	 ui32SysClock = Board_initGeneral(120*1000*1000);

	 /* Enable and configure the peripherals used by the UART0 */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

	//wait for Port A
	//while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));

	SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C8);
	GPIOPinConfigure(GPIO_PA2_I2C8SCL);
	GPIOPinConfigure(GPIO_PA3_I2C8SDA);
	GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_2);
	GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_3);

	I2CMasterInitExpClk(I2C8_BASE, ui32SysClock, false);
	I2CMasterEnable(I2C8_BASE);
	I2C_init();
 }


void IRThermo_Task(){

	I2C_Handle      handle;
	I2C_Params      i2cparams;
	//I2C_Transaction i2c --> in the function;
	// extern Mailbox_Handle mailbox1;
	int value = 0;
	MsgObj message_in;

	System_printf("checkpoint1: \n");
	System_flush();
	// setup_I2C();

	I2C_Params_init(&i2cparams);
	i2cparams.bitRate = I2C_100kHz;
	i2cparams.transferMode = I2C_MODE_BLOCKING;

	handle = I2C_open(EK_TM4C1294XL_I2C8, &i2cparams);
	if (handle == NULL)
	{
		System_abort("I2C was not opened");
	}
	else
	{
		System_printf("I2C opened\n");
		System_flush();
	}

	// Task_sleep(1000);

	while (true)
	{
		Task_sleep(50);
		value = I2Cread_16(MLX90614_TOBJ1, &handle);
		System_printf("Value: %d\n", value);
		Mailbox_post(mailbox1, &value, BIOS_WAIT_FOREVER);
		System_flush();

	//tempData = (tempData * tempFactor)-0.01;
		//float celcius = tempData - 273.15;
	}
}

void setup_IRThermo_Task(Mailbox_Handle mbox0) {

	Error_Block eb;
	Task_Params Params_Blink_Task;
	Task_Handle Handle_Blink_Task;

	Error_init(&eb);
	Task_Params_init(&Params_Blink_Task);
	Params_Blink_Task.stackSize = 512;/*stack in bytes*/
	Params_Blink_Task.priority = 15;/*15 is default 16 is highest priority -> see RTOS configuration*/
	Handle_Blink_Task = Task_create((Task_FuncPtr) IRThermo_Task, &Params_Blink_Task, &eb);
	if (Handle_Blink_Task == NULL)
	{
		System_abort("Task create failed");
	}

	System_printf("Task created:\n");
	mailbox1=mbox0;
}

uint16_t I2Cread_16(uint8_t radd, I2C_Handle *handle) {

	I2C_Transaction i2c;

	uint8_t readBuffer[2];
	uint8_t writeBuffer[3];
	uint16_t otemp;
	uint16_t atemp;
	uint16_t temp;
	uint16_t rbuf;
	uint16_t ambtemp;


	i2c.slaveAddress = DEVICE_ADDR;

	i2c.writeBuf = (uint8_t*) &writeBuffer[0];
	i2c.readBuf = (uint8_t*) &readBuffer[0];

	i2c.writeCount = 1;
	i2c.readCount = 2;
	writeBuffer[0] = radd; /*address to be read*/

	if (!I2C_transfer(*handle, &i2c)) {
		//GPIO_write(Board_LED1, Board_LED_ON);
		System_abort("Bad I2C transfer!");
	}

	rbuf = readBuffer[1] << 8;
	rbuf |= readBuffer[0];

	// --------

	i2c.writeCount = 1;
	i2c.readCount = 2;
	writeBuffer[0] = 0x06; /*ambient temperature address to be read*/

	if (!I2C_transfer(*handle, &i2c))
	{
		//GPIO_write(Board_LED1, Board_LED_ON);
		System_abort("Bad I2C transfer!");
	}

	ambtemp = readBuffer[1] << 8;
	ambtemp |= readBuffer[0];


	otemp = (rbuf * 0.02) - 273.15;
	atemp = (ambtemp * 0.02) - 273.15;

	temp = otemp;

	return temp;
}

