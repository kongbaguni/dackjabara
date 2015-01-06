//========================================================================
// CMath_Random.cpp -  a useful random number generator class
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
//  "Mersenne Twister pseudorandom number generator"
//  Original Code written by Takuji Nishimura and Makoto Matsumoto
//
//========================================================================

//========================================================================
//  Content References in Game Coding Complete
//
// class CRandom            - Chapter 3, pages 84-87
//
//========================================================================

#include <time.h>
#include "CRandom.h"

/////////////////////////////////////////////////////////////////////////////
// DEBUG info
/////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------

CRandom* CRandom::getInstnace()
{
	static CRandom* instance = NULL;
	if(instance==NULL)
	{
		instance = new CRandom();
		instance->SetRandomSeed(time(NULL));
	}
	return instance;
}

CRandom* CRandom::create()
{
	CRandom* rnd = new CRandom();
	rnd->autorelease();
	return rnd;
}

CRandom::CRandom(void)
{
	rseed = 1;
	// safe0 start
	rseed_sp = 0;
	mti=CMATH_N+1;
	// safe0 end
}   

unsigned int CRandom::Random()
{
	unsigned long y;
	static unsigned long mag01[2]={0x0, CMATH_MATRIX_A};

	/* mag01[x] = x * MATRIX_A  for x=0,1 */

	if (mti >= CMATH_N) { /* generate N words at one time */
		int kk;

		if (mti == CMATH_N+1)   /* if sgenrand() has not been called, */
			SetRandomSeed(4357); /* a default initial seed is used   */

		for (kk=0;kk<CMATH_N-CMATH_M;kk++) {
			y = (mt[kk]&CMATH_UPPER_MASK)|(mt[kk+1]&CMATH_LOWER_MASK);
			mt[kk] = mt[kk+CMATH_M] ^ (y >> 1) ^ mag01[y & 0x1];
		}
		for (;kk<CMATH_N-1;kk++) {
			y = (mt[kk]&CMATH_UPPER_MASK)|(mt[kk+1]&CMATH_LOWER_MASK);
			mt[kk] = mt[kk+(CMATH_M-CMATH_N)] ^ (y >> 1) ^ mag01[y & 0x1];
		}
		y = (mt[CMATH_N-1]&CMATH_UPPER_MASK)|(mt[0]&CMATH_LOWER_MASK);
		mt[CMATH_N-1] = mt[CMATH_M-1] ^ (y >> 1) ^ mag01[y & 0x1];

		mti = 0;
	}

	y = mt[mti++];
	y ^= CMATH_TEMPERING_SHIFT_U(y);
	y ^= CMATH_TEMPERING_SHIFT_S(y) & CMATH_TEMPERING_MASK_B;
	y ^= CMATH_TEMPERING_SHIFT_T(y) & CMATH_TEMPERING_MASK_C;
	y ^= CMATH_TEMPERING_SHIFT_L(y);

	return y;
}

// Returns a number from 0 to n (excluding n)
unsigned int CRandom::Random( unsigned int n )
{
	if( n == 0 )
		return 0;
	// ET - old engine added one to the result.
	// We almost NEVER wanted to use this function
	// like this.  So, removed the +1 to return a
	// range from 0 to n (not including n).
	return (Random()%n);
}

void CRandom::SetRandomSeed(unsigned int n)
{
	/* setting initial seeds to mt[N] using         */
	/* the generator Line 25 of Table 1 in          */
	/* [KNUTH 1981, The Art of Computer Programming */
	/*    Vol. 2 (2nd Ed.), pp102]                  */
	mt[0]= n & 0xffffffff;
	for (mti=1; mti<CMATH_N; mti++)
		mt[mti] = (69069 * mt[mti-1]) & 0xffffffff;

	rseed = n;
}

unsigned int CRandom::GetRandomSeed(void)
{
	return(rseed);
}

void CRandom::Randomize(void)
{
	SetRandomSeed((unsigned int)time(NULL));
}

//--------------------------------------------------------------------------------
// EOF