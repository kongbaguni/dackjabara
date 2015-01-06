#ifndef __APP_CRANDOM_H__
#define __APP_CRANDOM_H__
//========================================================================
// CMath.h -  useful and fast math functions and approximations
//
// Part of the GameCode Application
//
// GameCode is the sample application that encapsulates much of the source code
// discussed in "Game Coding Complete" by Mike McShaffry, published by
// Paraglyph Press. ISBN: 1-932111-75-1
//
// If this source code has found it's way to you, and you think it has helped you
// in any way, do the author a favor and buy a new copy of the book - there are
// detailed explanations in it that compliment this code well. Buy a copy at Amazon.com
// by clicking here: http://www.amazon.com/exec/obidos/ASIN/1932111751/gamecodecompl-20/
//
// There's also a companion web site at http://www.mcshaffry.com/GameCode/portal.php
//
// (c) Copyright 2003 Michael L. McShaffry
//
// This work is licensed under the Creative Commons Attribution-ShareAlike License.
// To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/1.0/
// or send a letter to:
//      Creative Commons
//      559 Nathan Abbott Way
//      Stanford, California 94305, USA.
//
//========================================================================

//========================================================================
//
//  Original Code written at Compulsive Development
//
//========================================================================

//========================================================================
//  Content References in Game Coding Complete
//
// class CRandom            - Chapter 3, pages 84-87
//
//========================================================================

//--------------------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------------------

#include <functional>
#include <vector>
//--------------------------------------------------------------------------------
// Defines
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------

/* Period parameters */
#define CMATH_N 624
#define CMATH_M 397
#define CMATH_MATRIX_A 0x9908b0df   /* constant vector a */
#define CMATH_UPPER_MASK 0x80000000 /* most significant w-r bits */
#define CMATH_LOWER_MASK 0x7fffffff /* least significant r bits */

/* Tempering parameters */
#define CMATH_TEMPERING_MASK_B 0x9d2c5680
#define CMATH_TEMPERING_MASK_C 0xefc60000
#define CMATH_TEMPERING_SHIFT_U(y)  (y >> 11)
#define CMATH_TEMPERING_SHIFT_S(y)  (y << 7)
#define CMATH_TEMPERING_SHIFT_T(y)  (y << 15)
#define CMATH_TEMPERING_SHIFT_L(y)  (y >> 18)

#include "cocos2d.h"
USING_NS_CC;

class CRandom : public cocos2d::Ref
{
private:
	// DATA
	unsigned int        rseed;
	unsigned int        rseed_sp;
	unsigned long mt[CMATH_N]; /* the array for the state vector  */
	int mti; /* mti==N+1 means mt[N] is not initialized */
	// FUNCTIONS
public:
	static CRandom* getInstnace();
	CRandom(void);  
	static CRandom* create();

	unsigned int    Random();
	unsigned int    Random( unsigned int n );

	void            SetRandomSeed(unsigned int n);
	unsigned int    GetRandomSeed(void);
	void            Randomize(void);
};

#endif//__APP_CRANDOM_H__
