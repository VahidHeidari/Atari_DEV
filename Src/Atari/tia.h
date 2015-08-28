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
#define REFP0		0x000B
#define REFP1		0x000C
#define PF0			0x000D
#define PF1			0x000E
#define PF2			0x000F
#define RESP0		0x0010
#define RESP1		0x0011
#define RESM0		0x0012
#define RESM1		0x0013
#define RESBL		0x0014
#define AUDC0		0x0015
#define AUDC1		0x0016
#define AUDF0		0x0017
#define AUDF1		0x0018
#define AUDV0		0x0019
#define AUDV1		0x001A
#define GRP0		0x001B
#define GRP1		0x001C
#define ENAM0		0x001D
#define ENAM1		0x001E
#define ENABL		0x001F
#define HMP0		0x0020
#define HMP1		0x0021
#define HMM0		0x0022
#define HMM1		0x0023
#define HMBL		0x0024
#define VDELP0		0x0025
#define VDELP1		0x0026
#define VDELBL		0x0027
#define RESMP0		0x0028
#define RESMP1		0x0029
#define HMOVE		0x002A
#define HMCLR		0x002B
#define CXCLR		0x002C

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

/// Color luminosity
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

/// Player
typedef struct
{
	Reg gp;						/// Player graphics register
	Reg refp;					/// Reflection player register
	Reg vdelp;					/// Vertical delay player register
	Reg resp;
	Reg hm;						/// Horizontal motion register
} Player, *pPlayer;

/// Missile
typedef struct
{
	Reg enam;					/// Enable missile register
	Reg nusize;					/// Number-size register
	Reg resm;
	Reg hm;						/// Horizontal motion register
} Missile, *pMissile;

/// Ball
typedef struct
{
	Reg ball;
	Reg resbl;
	Reg hm;						/// Horizontal motion register
} Ball, *pBall;

/// Collision
typedef union
{
	struct
	{
		Reg cxm0p;
		Reg cxm1p;
		Reg cxp0fb;
		Reg cxp1fb;
		Reg cxm0fb;
		Reg cxm1fb;
		Reg cxblpf;
		Reg cxppmm;
	} regs;

	Reg raw[8];
} Collision, *pCollision;

/// Sound registers
typedef struct
{
	Reg audc;					/// Tone. 4 bit audio control
	Reg audf;					/// Frequency. 5 bit audio frequency register
	Reg audv;					/// Volume. 4 bit audio volume register
} SoundRegs, *pSoundRegs;

/// Input
typedef union
{
	struct
	{
		/// Dumped inputs
		Reg inpt0;
		Reg inpt1;
		Reg inpt2;
		Reg inpt3;

		/// Latched inputs
		Reg inpt4;
		Reg inpt5;
	} regs;

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
uint8_t tia_read(uint16_t addr);

#ifdef __cplusplus
}
#endif

#endif

