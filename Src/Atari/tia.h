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

#ifndef TIA_H
#define TIA_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NUM_HORIZONTAL_LINES		262
#define NUM_VSYNC					3
#define NUM_VBLANK					37
#define NUM_TV_PICTURE_LINES		192
#define NUM_OVER_SCAN_LINES			30

#define CLOCK_LINE					228
#define CLOCK_HBLANK				68
#define CLOCK_VISIBLE				160
/// 1 CPU clock = 3 TIA clocks (228 / 3) = 76
#define CLOCK_CPU					76
#define CLOCK_FREQUENCY_MHZ			3.58
#define CLOCK_FREQUENCY				3580000

/// Write address
#define VSYNC		0x0000
#define VBLANK		0x0001
#define WSYNC		0x0002
#define RSYNC		0x0003
#define NUSIZ0		0x0004
#define NUSIZ1		0x0005
#define COLUP0		0x0006
#define COLUP1		0x0007
#define COLUPF		0x0008
#define COLUBK		0x0009
#define CTRLPF		0x000A

/// Read address
#define CXM0P		0x0000
#define CXM1P		0x0001
#define CXP0FB		0x0002
#define CXP1FB		0x0003
#define CXM0FB		0x0004
#define CXM1FB		0x0005
#define CXBLPF		0x0006
#define CXPPMM		0x0007
#define INPT0		0x0008
#define INPT1		0x0009
#define INPT2		0x000A
#define INPT3		0x000B
#define INPT4		0x000C
#define INPT5		0x000D

typedef uint8_t Reg;
typedef uint8_t ColorLum;

typedef union
{
	struct
	{
		ColorLum p0;			// P0, M0 (player0, Missile0)
		ColorLum p1;			// P1, M1 (player1, Missile1)
		ColorLum pf;			// PF, BL (playfield, ball)
		ColorLum bk;			// BK     (background)
	} colorlum;

	uint32_t colors;			// All colors

} ColorLuminosity, *pColorLuminosity;

/// Play field registers are 20 bits wide
typedef union
{
	struct
	{
		Reg pf0;				/// PF0 is only 4 bits wide.
		Reg pf1;				/// PF1 constructs next 8 bits.
		Reg pf2;				/// PF2 constructs last 8 bits.
	} regs;

	Reg raw[3];					/// All registers
} PlayFieldRegs, *pPlayFieldRegs;

typedef struct
{
	Reg gp;						/// Player graphics register
	Reg refp;					/// Reflection player register
	Reg vdelp;					/// Vertical delay player register
	Reg resp;
	Reg hm;						/// Horizontal motion register
} Player, *pPlayer;

typedef struct
{
	Reg enam;					/// Enable missile register
	Reg nusize;					/// Number-size register
	Reg resm;
	Reg hm;						/// Horizontal motion register
} Missile, *pMissile;

typedef struct
{
	Reg ball;
	Reg resbl;
	Reg hm;						/// Horizontal motion register
} Ball, *pBall;

typedef union
{
	struct
	{
		Reg _0;
		Reg _1;
	} regs;

	Reg raw[2];
    uint16_t all;
} Collision, *pCollision;

typedef struct
{
	Reg audc;					/// Tone. 4 bit audio control
	Reg audf;					/// Frequency. 5 bit audio frequency register
	Reg audv;					/// Volume. 4 bit audio volume register
} SoundRegs, *pSoundRegs;

typedef union
{
	struct
	{
		/// Dumped inputs
		Reg _0;
		Reg _1;
		Reg _2;
		Reg _3;

		/// Latched inputs
		Reg _4;
		Reg _5;
	} num;

	Reg raw[6];
} InputPort, *pInputPort;

/// Television Interface Adaptor
typedef struct
{
	PlayFieldRegs playfield;
	Player player_0;
	Player player_1;
	Missile missile_0;
	Missile missile_1;
	Ball ball;
	
	Reg ctlpf;					/// Control Play Feild
	Reg vdelpl;					/// Vertical Delay Ball register
	Reg hmclr;					/// Horizontal Motion Clear register
	Reg cxclr;					/// Collision Reset register

	Collision collision;

	SoundRegs sound_0;
	SoundRegs sound_1;

	InputPort input;
} TIA, *pTIA;

void tia_write(uint16_t addr, uint8_t value);
uint8_t read(uint16_t addr);

#ifdef __cplusplus
}
#endif

#endif

