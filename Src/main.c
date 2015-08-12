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


#include <stdio.h>

#include "config.h"
#include "debuger.h"
#include "console.h"

#ifdef __cplusplus
extern "C" {
#endif

int main(int argc, char** argv)
{
	int i;

	init_console();
	
    printf("This is Atari 2600 emulator!\n\n");
	
	// Print command line arguments.
	debug_message("argc : %d", argc);
	for (i = 0; i < argc; ++i)
		debug_message("argv[%2d] : %s", i, argv[i]);

    return 0;
}

#ifdef __cplusplus
}
#endif

