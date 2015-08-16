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
	
	Reg wsync;					/// Wait for SYNC
	Reg ctlpf;					/// Control Play Feild
	Reg vdelpl;					/// Vertical Delay Ball register
	Reg hmclr;					/// Horizontal Motion Clear register
	Reg cxclr;					/// Collision Reset register

	Collision collision;

	SoundRegs sound_0;
	SoundRegs sound_1;

	InputPort input;
} TIA, *pTIA;

#ifdef __cplusplus
}
#endif

#endif

