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

#include "pia.h"

#include "emulator.h"

void pia_write(uint16_t addr, uint8_t value)
{
	switch (addr)
	{
		case TIM1T : pia.timer.setting = Time1t; break;
		case TIM8T : pia.timer.setting = Time8t; break;
		case TIM64T: pia.timer.setting = Time64t; break;
		case T1024T: pia.timer.setting = Time1024t; break;
	}
	pia.timer.time = value;
	pia.timer.start_time = clock_cycle;
}

uint8_t pia_read(uint16_t addr)
{
	if (addr == INTIM)
		return pia.timer.time;

	return 0;
}

void pia_clock(void)
{
}

