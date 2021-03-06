/*
	Molole - Mobots Low Level library
	An open source toolkit for robot programming using DsPICs

	Copyright (C) 2007--2011 Stephane Magnenat <stephane at magnenat dot net>,
	Philippe Retornaz <philippe dot retornaz at epfl dot ch>
	Mobots group (http://mobots.epfl.ch), Robotics system laboratory (http://lsro.epfl.ch)
	EPFL Ecole polytechnique federale de Lausanne (http://www.epfl.ch)

	See authors.txt for more details about other contributors.

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published
	by the Free Software Foundation, version 3 of the License.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _MOLOLE_UART_H
#define _MOLOLE_UART_H

#include "../types/types.h"

/** \addtogroup uart */
/*@{*/

/** \file
	UART wrapper definitions
*/

// Defines

/** Identifiers of available UARTs. */
enum uart_identifiers
{
	UART_1 = 0,			/**< first UART */
	UART_2				/**< second UART */
};

/** Errors UART can throw */
enum uart_errors
{
	UART_ERROR_BASE = 0x0600,
	UART_ERROR_INVALID_ID,			/**< The specified UART does not exists. */
}; 


/** UART callback when a byte is received
	Return true if new data is accepted, false otherwise. */
typedef bool (*uart_byte_received)(int uart_id, unsigned char data, void* user_data);

/** UART callback when tx is available
	Return true if a new one should be sent, false otherwise. */
typedef bool (*uart_tx_ready)(int uart_id, unsigned char* data, void* user_data);

// Functions, doc in the .c

void uart_init(
	int uart_id,
	unsigned long baud_rate,
	bool hardware_flow_control,
	uart_byte_received byte_received_callback,
	uart_tx_ready tx_ready_callback,
	int priority,
	void* user_data
);

bool uart_transmit_byte(int uart_id, unsigned char data);

void uart_read_pending_data(int uart_id);

void uart_enable_tx_interrupt(int uart_id, int flags);

int uart_disable_tx_interrupt(int uart_id);


/*@}*/

#endif
