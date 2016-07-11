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

#include "config.h"
#include "emulator.h"
#include "debuger.h"

void tia_write(uint16_t addr, uint8_t value)
{
	switch (addr)
	{
		// Strobe addresses
		// Wait for leading edge of horizontal blank.
		case WSYNC: break;

		// Reset horizontal sync counter.
		case RSYNC: break;

		// Reset player 0.
		case RESP0: break;

		// Reset player 1.
		case RESP1: break;

		// Reset missile 0.
		case RESM0: break;

		// Reset missile 1.
		case RESM1: break;

		// Reset ball.
		case RESBL: break;

		// Apply horizontal motion.
		case HMOVE: break;

		// Clear horizontal motion registers.
		case HMCLR: break;

		// Clear collision latches.
		case CXCLR: 
			atari_2600.tia.collision.raw[0] = atari_2600.tia.collision.raw[1] =
			atari_2600.tia.collision.raw[2] = atari_2600.tia.collision.raw[3] =
			atari_2600.tia.collision.raw[4] = atari_2600.tia.collision.raw[5] =
			atari_2600.tia.collision.raw[6] = atari_2600.tia.collision.raw[7] = 0;
			break;

		// Other addresses

		default:
			log_error("Invalid write to TIA value of 0x%02x at $%04x.", value, addr);
			break;
	}
}

uint8_t tia_read(uint16_t addr)
{
	if (addr <= CXPPMM)
		return tia.collition.raw[addr];
	else if (addr <= INPT5)
		return tia.input.raw[addr - INPT0];

	log_error("Reading invalid address of 0x%04x of TIA", addr);
	return 0;
}

