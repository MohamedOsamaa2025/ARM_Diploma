/*
 * main.c
 *
 *  Created on: Apr 17, 2024
 *      Author: Lenovo
 */


#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"

#include "../include/RCC_interface.h"
#include "../include/GPIO_interface.h"
#include "../include/NVIC_interface.h"
#include "../include/EXTI_interface.h"

void led1(void);
void led2(void);


void main(void)
{
	RCC_voidInit();

	RCC_voidEnablePeripheralClock(RCC_AHB, RCC_AHB_GPIOAEN);
	RCC_voidEnablePeripheralClock(RCC_AHB, RCC_AHB_GPIOBEN);

	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN1, GPIO_OUTPUT);
	MGPIO_voidSetPinOutputSpeed(GPIO_PORTA, GPIO_PIN1, GPIO_LOW_SPEED);
	MGPIO_voidSetPinOutputType(GPIO_PORTA, GPIO_PIN1, GPIO_OUTPUT_PP);
	MGPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN0, GPIO_OUTPUT);
	MGPIO_voidSetPinOutputSpeed(GPIO_PORTB, GPIO_PIN0, GPIO_LOW_SPEED);
	MGPIO_voidSetPinOutputType(GPIO_PORTB, GPIO_PIN0, GPIO_OUTPUT_PP);

	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN0, GPIO_INPUT);
	MGPIO_voidSetPullUpDownResistor(GPIO_PORTA, GPIO_PIN0,GPIO_PULL_UP);
	MGPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN1, GPIO_INPUT);
	MGPIO_voidSetPullUpDownResistor(GPIO_PORTB, GPIO_PIN1,GPIO_PULL_UP);

	RCC_voidEnablePeripheralClock(RCC_APB2, RCC_APB2_SYSCFGEN);

	MNVIC_voidInit();

	/*Enable Interrupt For EXTI0*/
	MNVIC_voidPeripheralInterruptControl(6, MNVIC_INT_ENABLE);
	/*Enable Interrupt For EXTI1*/
	MNVIC_voidPeripheralInterruptControl(7, MNVIC_INT_ENABLE);
	/*Set The EXTI0 Priority*/
	MNVIC_voidSetPeripheralPriority(6, 0b0001); // EXTI0 : GRP 0 SUB 1
	/*Set The EXTI1 Priority*/
	MNVIC_voidSetPeripheralPriority(7, 0b0110); // EXTI1 : GRP 1 SUB 2


//	MEXTI_voidInit();

	MEXTI_voidEnableInterrupt(MEXTI_EXTI0);
	MEXTI_voidEnableInterrupt(MEXTI_EXTI1);
	MEXTI_voidChangePin(MEXTI_EXTI0,PortA);
	MEXTI_voidChangePin(MEXTI_EXTI1,PortB);
	MEXTI_voidChangeSenseMode(MEXTI_EXTI0,MEXTI_FALLING);
	MEXTI_voidChangeSenseMode(MEXTI_EXTI1,MEXTI_FALLING);

	MEXTI_voidSetCallBack(MEXTI_EXTI0,&led1);
	MEXTI_voidSetCallBack(MEXTI_EXTI1,&led2);

	while(1)
	{
		asm("NOP");
	}
}

void led1(void)
{
	static u8 Local_u8LEDState = 0;
	Local_u8LEDState ^= 1;
	MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN1, Local_u8LEDState);
}
void led2(void)
{
	static u8 Local_u8LEDState = 0;
	Local_u8LEDState ^= 1;
	MGPIO_voidSetPinValue(GPIO_PORTB, GPIO_PIN0, Local_u8LEDState);
}

