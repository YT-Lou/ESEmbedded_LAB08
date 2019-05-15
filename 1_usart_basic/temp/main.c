#include <stdint.h>
#include "reg.h"

void init_usart1(void)
{
	//PB6 PB7

	//RCC EN GPIOB
	//??????
        SET_BIT(RCC_BASE + RCC_CR_OFFSET, HSERDY_BIT);
	CLEAR_BIT(RCC_BASE + RCC_CR_OFFSET, HSEON_BIT);

	//GPIO Configurations
	//??????
        SET_BIT(GPIO_BASE(GPIO_PORTB) + GPIOx_MODER_OFFSET, MODERy_1_BIT(4));
	CLEAR_BIT(GPIO_BASE(GPIO_PORTB) + GPIOx_MODER_OFFSET, MODERy_0_BIT(4));

	//RCC EN USART1
	//??????
        SET_BIT(USART_BASE(GPIO_PORTC) + USART_SR_OFFSET, TXE_BIT(6));
	CLEAR_BIT(USART_BASE(GPIO_PORTC) + USART_SR_OFFSET, RXNE_BIT(7));

	//Baud
	const unsigned int BAUD = 115200;
	const unsigned int SYSCLK_MHZ = 168;
	const double USARTDIV = SYSCLK_MHZ * 1.0e6 / 16 / BAUD;

	const uint32_t DIV_MANTISSA = (unit32_t)USARDIV;//??????
	const uint32_t DIV_FRACTION = (unit32_t)((USARDIV-DIV_MANTISSA)*16)//??????

	//USART  Configurations
	//??????
        SET_BIT(USART1_BASE +USART_CR1_OFFSET, UE_BIT);
        SET_BIT(USART1_BASE +USART_CR1_OFFSET, TE_BIT);
        SET_BIT(USART1_BASE +USART_CR1_OFFSET, RE_BIT);

}

void usart1_send_char(const char ch)
{
	//??????
        while(!READ_BIT(USART1_BASE +USART_SR_OFFSET,TXE_BIT))
                 ;
             REG(USART1_BASE +USART_SR_OFFSET) +ch;
}

char usart1_receive_char(void)
{
	//??????
        while(!READ_BIT(USART1_BASE +USART_SR_OFFSET,RXNE_BIT))
             ;
         REG(USART1_BASE +USART_DR_OFFSET);
}

int main(void)
{
	init_usart1();

	char *hello = "Hello world!\r\n";

	//send Hello world
	while (*hello != '\0')
		usart1_send_char(*hello++);


	//receive char and resend it
	char ch;
	while (1)
	{
		ch = usart1_receive_char();

		if (ch == '\r')
			usart1_send_char('\n');

		usart1_send_char(ch);
	}
}
