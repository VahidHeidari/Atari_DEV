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

#include "tia.h"

#include <string.h>

#include "config.h"
#include "emulator.h"
#include "debuger.h"

int tia_init(pTIA tia)
{
	memset(tia, 0, sizeof(TIA));
	return 1;
}

void tia_close(pTIA tia)
{
	(void)tia;
}

void tia_write(uint16_t addr, uint8_t value)
{
	(void)value;

	switch (addr)
	{
		case WSYNC:
			break;
		case RSYNC:
			break;
		default:
			break;
	}
}

uint8_t tia_read(uint16_t addr)
{
	if (addr <= CXPPMM)
		return tia.collision.raw[addr];
	else if (addr <= INPT5)
		return tia.input.raw[addr - INPT0];

	log_error("Reading invalid address of 0x%04x of tia", addr);
	return 0;
}

