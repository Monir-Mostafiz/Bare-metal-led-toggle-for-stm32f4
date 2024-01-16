/*
 * uart.h
 *
 *  Created on: Sep 25, 2023
 *      Author: User
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f446xx.h"
#include <stdint.h>

void uart2_tx_init(void);
char uart2_read(void);
void uart2_rxtx_init(void);

#endif /* UART_H_ */
