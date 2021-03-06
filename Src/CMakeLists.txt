#
# Atari_DEV is a cross-platform, portable, and hand-held Atari 2600 emulator.
#
# Copyright (C) 2015  Vahid Heidari (DeltaCode)
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

cmake_minimum_required(VERSION 2.8)

project(Atari2600)

set(CMAKE_USE_RELATIVE_PATHS true)

include_directories(Atari TUI .)

add_executable(Atari_DEV
    main.c
	Atari/cycles.c
    Atari/debuger.c
	Atari/emulator.c
	Atari/p6502.c
	Atari/pia.c
	Atari/tia.c
    TUI/console.c
	)

if(MSVC)
    set_property(TARGET Atari_DEV APPEND_STRING PROPERTY COMPILE_FLAGS /W3)
elseif(CMAKE_COMPILER_IS_GNUCC)
	add_definitions(-Wall -Wextra -Wconversion -pedantic -Werror -std=c99)
    target_link_libraries(Atari_DEV SDL2 SDL2main)

	if (CMAKE_SYSTEM_NAME STREQUAL Windows)
		add_definitions(-mwindows)
        target_link_libraries(Atari_DEV mingw32)
	endif()
	
	if(CMAKE_BUILD_TYPE STREQUAL Release)
		add_definitions(-O3)
	endif()
endif(MSVC)

