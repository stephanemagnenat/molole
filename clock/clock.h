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

#ifndef _MOLOLE_CLOCK_H
#define _MOLOLE_CLOCK_H

#include "../types/types.h"

/** \addtogroup clock */
/*@{*/

/** \file
	\brief Clock configuration
*/

// defines

// oscillator selection: Fast RC or External Clock
enum clock_type {
	CLOCK_FRC = 0,		// Fast RC oscillator (FRC)
	CLOCK_FRCPLL,			// Fast RC oscillator (FRC) with PLL
	CLOCK_PRIM,			// Primary oscillator (XT, HS, EC)
	CLOCK_PRIMPLL,		// Primary oscillator (XT, HS, EC) with PLL
	CLOCK_SEC,			// Secondary oscillator (SOSC)
	CLOCK_LOW,			// Low-Power RC oscillator (LPRC)
	CLOCK_FRCDIV16,		// Fast RC oscillator (FRC) with Divide-by-16
	CLOCK_FRCDIVN,		// Fast RC oscillator (FRC) with Divide-by-n
};

// Functions, doc in the .c

void clock_init_internal_rc_from_n1_m_n2(unsigned n1, unsigned m, unsigned n2);

void clock_init_external_clock_from_n1_m_n2(unsigned n1, unsigned m, unsigned n2, unsigned long source_freq);

void clock_init_internal_rc_30();

void clock_init_internal_rc_40();

void clock_set_speed(unsigned long hz, unsigned int mips);

unsigned long clock_get_cycle_duration();

unsigned long clock_get_cycle_frequency();

unsigned clock_get_target_bogomips();

void clock_disable_idle();

void clock_enable_idle();

void clock_idle();

void clock_delay_us(unsigned int us);

// Microchip Idle() implementation has a "non wanted feature", it doesn't have a barrier
// So you cannot while(test) Idle(); on a variable with GCC -03 optimisation
// Gcc will transform it into a if(test) { while(1) { Idle(); } }
#ifdef Idle
#undef Idle
#endif

#define Idle() do { clock_idle(); barrier(); } while(0)


/*@}*/

#endif
