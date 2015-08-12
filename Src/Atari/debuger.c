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

#include "debuger.h"

#include <string.h>
#include <stdio.h>
#include <stdarg.h>

void log_info(const char* str, ...)
{
#ifdef DEBUG_LOGGING
	va_list args;
	FILE* f = fopen("log.txt", "a");
	if (!f)
		return;
	fprintf(f, "INFO    : ");
	va_start(args, str);
	vfprintf(f, str, args);
	va_end(args);
	fprintf(f, "\n");
	fclose(f);
#else
	(void)str;
#endif
}

void log_warning(const char* str, ...)
{
#ifdef DEBUG_LOGGING
	va_list args;
	FILE* f = fopen("log.txt", "a");
	if (!f)
		return;
	va_start(args, str);
	fprintf(f, "WARNING : ");
	vfprintf(f, str, args);
	fprintf(f, "\n");
	va_end(args);
	fclose(f);
#else
	(void)str;
#endif
}

void log_error(const char* str, ...)
{
#ifdef DEBUG_LOGGING
	va_list args;
	FILE* f = fopen("log.txt", "a");
	if (!f)
		return;
	va_start(args, str);
	fprintf(f, "ERROR   : ");
	vfprintf(f, str, args);
	fprintf(f, "\n");
	va_end(args);
	fclose(f);
#else
	(void)str;
#endif
}

void debug_message(const char* str, ...)
{
#if defined DEBUG_MODE
	va_list args;

	va_start(args, str);
	vprintf(str, args);
	putchar('\n');
	va_end(args);
#endif
}

