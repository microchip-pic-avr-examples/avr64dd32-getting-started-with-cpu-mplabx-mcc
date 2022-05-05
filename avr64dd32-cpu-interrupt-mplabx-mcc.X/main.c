 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
© [2022] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include <util/delay.h>

#define PULSE_TIME                  1000 /* time in ms */

/*
    Main application
*/

static void USART0_sendChar(char c)
{
    while (!(USART0.STATUS & USART_DREIF_bm))
    {
        ;
    }        
    USART0.TXDATAL = c;
}

void USART0_RX_INT(void)
{
    char c = USART0.RXDATAL;
    /* Echo the received character */
    USART0_sendChar(c);
}

void TCB0_INT(void)
{    /* Clear the interrupt flag */
    TCB0.INTFLAGS |= TCB_CAPT_bm;
    LED0_SetLow();
    _delay_ms(PULSE_TIME);
}

void TCB1_INT(void)
{    /* Clear the interrupt flag */
    TCB1.INTFLAGS |= TCB_CAPT_bm;
    LED0_SetHigh();
    _delay_ms(PULSE_TIME);
}

int main(void)
{
    SYSTEM_Initialize();

    USART0_RxCompleteCallbackRegister(USART0_RX_INT);
    TCB0_CaptureCallbackRegister(TCB0_INT);
    TCB1_CaptureCallbackRegister(TCB1_INT);
    
    while(1)
    {
        ;
    }    
}