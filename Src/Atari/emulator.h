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

#ifndef EMULATOR_H_
#define EMULATOR_H_

#include "p6502.h"
#include "pia.h"
#include "tia.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	int hsync_counter;

	P6502 p;
	PIA pia;
	TIA tia;
} Atari2600, *pAtari2600;

extern Atari2600 atari_2600;
extern int finished_emulation;

int emulator_init(void);
void emulator_close(void);
int emulator_save_state(const char* path);
int emulator_load_state(const char* path);
int emulator_read_rom_image(const char* path);
void step(void);
void run(void);
void run_cycles(int cycles);

#ifdef __cplusplus
}
#endif

#endif

