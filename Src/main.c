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

#include <stdlib.h>
#include <stdio.h>

#include "config.h"
#include "debuger.h"
#include "console.h"
#include "emulator.h"

#ifdef __cplusplus
extern "C" {
#endif

void print_regs(pP6502 p)
{
	printf("    A  : %02X            PC : %04X\n", p->a, p->pc.w);
	printf("    X  : %02X            P  : %02X\n", p->x, p->p);
	printf("    Y  : %02X            N V   B D I Z C\n", p->y);
	printf("    SP : %02X            %c %c %c %c %c %c %c %c\n",
			p->sp,
			p->p & N_FLAG ? '1' : '0',
			p->p & V_FLAG ? '1' : '0',
			p->p & FLAG_1 ? '1' : '0',
			p->p & B_FLAG ? '1' : '0',
			p->p & D_FLAG ? '1' : '0',
			p->p & I_FLAG ? '1' : '0',
			p->p & Z_FLAG ? '1' : '0',
			p->p & C_FLAG ? '1' : '0');
	printf("    cc : %d\n\n", p->cycle_counter);
}

void update_regs(void)
{
	gotoxy(REGS_X, REGS_Y);
	print_regs(&p);
}

int main(int argc, char** argv)
{
	int i;
	int cmd;
	unsigned int val;
	unsigned int addr;

    printf("This is Atari 2600 emulator!\n\n");
	
	// Print command line arguments.
	debug_message("argc : %d", argc);
#if DEBUG_MODE
	for (i = 0; i < argc; ++i)
		debug_message("argv[%2d] : %s", i, argv[i]);
#endif

	if (argc < 2) {
		printf("Emulation failed! No ROM image supplied!\n");
		return 1;
	}

	if (emulator_init() != 1) {
		printf("Emulator initialization failed!\n");
		return 1;
	}

	init_console();
	gotoxy(REGS_X, REGS_Y);
	update_regs();

	while (!finished_emulation) {
		clear_cmd_line();
		cmd = getch();

		switch (cmd) {
			case 'q':
			case 'Q':
				finished_emulation = 1;
				break;

			case 's':
			case 'S':
				step();
				update_regs();
				break;

			case 'c':
			case 'C':
				if (scanf_s("%u", &val)) {
					run_cycles((int)val);
					update_regs();
				}
				break;

			case 'r':
			case 'R':
				if (scanf_s("%4x", &addr)) {
					val = read((uint16_t)addr);
					printf("    $%04x : $%02x", addr, val);
				}
				break;
		}
	}

	emulator_close();

    return 0;
}

#ifdef __cplusplus
}
#endif

