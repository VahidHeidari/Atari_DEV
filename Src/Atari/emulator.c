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

#include "emulator.h"

P6502 p;
PIA pia;
TIA tia;

long long clock_cycle;
int finished_emulation;

int emulator_init(void)
{
	finished_emulation = 0;

	if (pia_init(&pia) != 1)
		return 0;

	if (tia_init(&tia) != 1)
		return 0;

	power_on(&p);

	return 1;
}

void emulator_close(void)
{
	finished_emulation = 1;
}

int emulator_save_state(const char* path)
{
	(void)path;
	return 1;
}

int emulator_load_state(const char* path)
{
	(void)path;
	return 1;
}

int emulator_read_rom_image(const char* path)
{
	(void)path;
	return 1;
}

void step(void)
{
	fetch(&p);
}

void run(void)
{
	while (!finished_emulation)
		step();
}

void run_cycles(int cycles)
{
	long long end_cycle = p.cycle_counter + cycles;

	while (p.cycle_counter < end_cycle && !finished_emulation)
		step();
}

