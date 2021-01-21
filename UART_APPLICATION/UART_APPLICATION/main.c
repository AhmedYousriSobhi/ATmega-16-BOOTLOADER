/*
 * UART_APPLICATION.c
 *
 * Created: 12/30/2020 4:15:06 PM
 * Author : kidna
 */ 

#include <avr/io.h>

void USART_Init( unsigned int baud );
void USART_Transmit( unsigned char data );
void USART_Transmit_Msg(uint8_t *word );
uint8_t messege[]= "HELLO FROM APPLICATION\n";

int main(void)
{
    USART_Init(12); // setting baudrate to 4800
    while (1) 
    {
		USART_Transmit_Msg((uint8_t *)"HELLO FROM APPLICATION\n");
		USART_Transmit_Msg((uint8_t *)"YOU HAVE DONE YOUR FIRST BOOTLOADER CODE\n");
    }
}

void USART_Init( uint16_t baud )
{
	/* Set baud rate */
	UBRRH = (unsigned char)(baud>>8);
	UBRRL = (unsigned char)baud;
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 1stop bit */
	UCSRC = (1<<URSEL)|(3<<UCSZ0);
}

void USART_Transmit( uint8_t data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) )
	;
	/* Put data into buffer, sends the data */
	UDR = data;
}

void USART_Transmit_Msg(uint8_t *word )
{
	uint8_t index = 0;
	while(word[index] != '\n')
	{
		USART_Transmit(word[index++]);
	}
	USART_Transmit('\n');
	
}