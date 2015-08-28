/**
 * Atari_DEV is a cross-platform, portable, and hand-held Atari 2600 emulator.
 *
 * Copyright (C) 2015  Vahid Heidari (DeltaCode)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PIA_H_
#define PIA_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PIA_RAM_SIZE		128
#define PIA_RAM_START		0x80
#define PIA_RAM_END			0xFF

/// PortA read/write address
#define SWCHA				0x280
/// Joystick controllers
#define SWCHA_P0_RIGHT		0x80
#define SWCHA_P0_LEFT		0x40
#define SWCHA_P0_DOWN		0x20
#define SWCHA_P0_UP			0x10
#define SWCHA_P1_RIGHT		0x08
#define SWCHA_P1_LEFT		0x04
#define SWCHA_P1_DOWN		0x02
#define SWCHA_P1_UP			0x01
/// Paddle (pot) controllers
#define SWCHA_NOT_USED_BITS	0x33
#define SWCHA_P0_TRIGGER	0x80
#define SWCHA_P1_TRIGGER	0x40
#define SWCHA_P2_TRIGGER	0x08
#define SWCHA_P3_TRIGGER	0x04

/// PoartA DDR register address; 0=input, 1=output
#define SWACNT				0x281

/// PortB; console switches (read only)
#define SWCHB				0x282

/// PortB DDR (hardwired as input)
#define SWBCNT				0x283

/// Timer output address (read only)
#define INTIM				0x284

/// Interval setting address
#define TIM1T				0x294
#define TIM8T				0x295
#define TIM64T				0x296
#define T1024T				0x297

typedef enum
{
	Time1t,
	Time8t,
	Time64t,
	Time1024t
} TimerSetting;

typedef struct
{
	TimerSetting setting;
	int start_time;
	int time;
} Timer;

typedef struct
{
	uint8_t DDR;
	uint8_t data;
} PortA, *pPortA;

typedef struct
{
	Timer timer;
	PortA porta;
	uint8_t portb;
	uint8_t RAM[PIA_RAM_SIZE];
} PIA, *pPIA;

void pia_write(uint16_t addr, uint8_t value);
uint8_t pia_read(uint16_t addr);
void pia_clock(void);

#ifdef __cplusplus
}
#endif

#endif

