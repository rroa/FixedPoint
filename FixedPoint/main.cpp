#include <iostream>
#include "FixedPoint.h"
#include <assert.h>
#include <cmath>
#include <cfloat>

const float EPSIL = 0.001f;

#define TESTARITHMETIC 1
#define TESTLOGICAL 1
#define TESTCOMPARISONS 1
#define TESTTRIG 1

#define FIXEDPOINT_TESTER(assertFunc) \
	std::cout << #assertFunc << std::endl; \
	assert( assertFunc );

bool nearlyEqual(float a, float b, float epsilon);

void TestsFixed()
{
#if TESTARITHMETIC
	fixed16_t one		= 1.0;
	fixed16_t two		= 2.0;
	fixed16_t minus10	= -10.0;
	std::cout << "==================================================" << std::endl;
	std::cout << "==   DOUBLE ARITHMETIC  ==" << std::endl;
	std::cout << "==================================================" << std::endl;
	FIXEDPOINT_TESTER( one + two == 3.0 );
	FIXEDPOINT_TESTER( two + one == 3.0 );
	FIXEDPOINT_TESTER( two - one == 1.0 );
	FIXEDPOINT_TESTER( two * one == 2.0 );
	FIXEDPOINT_TESTER( two / one == 2.0 );

	FIXEDPOINT_TESTER( one + minus10 == -9.0 );
	FIXEDPOINT_TESTER( minus10 + one == -9.0 );
	FIXEDPOINT_TESTER( minus10 - one == -11.0 );
	FIXEDPOINT_TESTER( minus10 * one == -10.0 );
	FIXEDPOINT_TESTER( minus10 / one == -10.0 );

	FIXEDPOINT_TESTER( two + minus10 == -8.0 );
	FIXEDPOINT_TESTER( minus10 + two == -8.0 );
	FIXEDPOINT_TESTER( minus10 - two == -12.0 );
	FIXEDPOINT_TESTER( minus10 * two == -20.0 );
	FIXEDPOINT_TESTER( minus10 / two == -5.0 );

	FIXEDPOINT_TESTER( 3.0  == ( one += two ));
	FIXEDPOINT_TESTER( 8.0  == ( one -= -5 ));
	FIXEDPOINT_TESTER( 16.0 == ( one *= two ));
	FIXEDPOINT_TESTER( 4.0  == ( one /= 4 ));

	fixed16_t SPone		= (float)1.0;
	fixed16_t SPtwo		= (float)2.0;
	fixed16_t SPminus10 = (float)-10.0;

	int mda = 3;
	fixed16_t da = 3.0f;

	FIXEDPOINT_TESTER( da % 2  == mda % 2 );	
	da %= 2;
	mda %= 2;
	FIXEDPOINT_TESTER( da == mda );

	std::cout << "==================================================" << std::endl;
	std::cout << "==   FLOAT ARITHMETIC  ==" << std::endl;
	std::cout << "==================================================" << std::endl;
	FIXEDPOINT_TESTER( SPone + SPtwo == ( float ) 3.0 );
	FIXEDPOINT_TESTER( SPtwo + SPone == ( float ) 3.0 );
	FIXEDPOINT_TESTER( SPtwo - SPone == ( float ) 1.0 );
	FIXEDPOINT_TESTER( SPtwo * SPone == ( float ) 2.0 );
	FIXEDPOINT_TESTER( SPtwo / SPone == ( float ) 2.0 );

	FIXEDPOINT_TESTER( SPone + SPminus10 == ( float ) -9.0 );
	FIXEDPOINT_TESTER( SPminus10 + SPone == ( float ) -9.0 );
	FIXEDPOINT_TESTER( SPminus10 - SPone == ( float ) -11.0 );
	FIXEDPOINT_TESTER( SPminus10 * SPone == ( float ) -10.0 );
	FIXEDPOINT_TESTER( SPminus10 / SPone == ( float ) -10.0 );

	FIXEDPOINT_TESTER( SPtwo + SPminus10 == ( float ) -8.0 );
	FIXEDPOINT_TESTER( SPminus10 + SPtwo == ( float ) -8.0 );
	FIXEDPOINT_TESTER( SPminus10 - SPtwo == ( float ) -12.0 );
	FIXEDPOINT_TESTER( SPminus10 * SPtwo == ( float ) -20.0 );
	FIXEDPOINT_TESTER( SPminus10 / SPtwo == ( float ) -5.0 );

	FIXEDPOINT_TESTER( 3.0  == ( SPone += SPtwo ));
	FIXEDPOINT_TESTER( 8.0  == ( SPone -= -5 ));
	FIXEDPOINT_TESTER( 16.0 == ( SPone *= SPtwo ));
	FIXEDPOINT_TESTER( 4.0  == ( SPone /= 4 ));

	int mfa = 3;
	fixed16_t fma = 3.0f;

	FIXEDPOINT_TESTER( fma % 2  == mfa % 2 );	
	fma %= 2;
	mfa %= 2;
	FIXEDPOINT_TESTER( fma == mfa );
#endif

#if TESTCOMPARISONS
	fixed16_t a1;
	fixed16_t a2= 3.1415;
	fixed16_t a3= a1 + a2;
	std::cout << "==================================================" << std::endl;
	std::cout << "==   COMPARISONS  ==" << std::endl;
	std::cout << "==================================================" << std::endl;
	FIXEDPOINT_TESTER( a3 <  ( float ) 3.1416 );
	FIXEDPOINT_TESTER( a3 >  ( float ) 3.1414 );
	FIXEDPOINT_TESTER( a3 <= ( float ) 3.1416 );
	FIXEDPOINT_TESTER( a3 >= ( float ) 3.1414 );
	FIXEDPOINT_TESTER( a3 == ( float ) 3.1415 );
	FIXEDPOINT_TESTER( a3 != ( float ) 3.1414 );

	FIXEDPOINT_TESTER(( float ) 3.1416 > a3 );
	FIXEDPOINT_TESTER(( float ) 3.1414 < a3 );
	FIXEDPOINT_TESTER(( float ) 3.1416 >= a3 );
	FIXEDPOINT_TESTER(( float ) 3.1414 <= a3 );
	FIXEDPOINT_TESTER(( float ) 3.1415 == a3 );
	FIXEDPOINT_TESTER(( float ) 3.1414 != a3 );


	FIXEDPOINT_TESTER( a3 < 3.1416 );
	FIXEDPOINT_TESTER( a3 > 3.1414 );
	FIXEDPOINT_TESTER( a3 <= 3.1416 );
	FIXEDPOINT_TESTER( a3 >= 3.1414 );
	FIXEDPOINT_TESTER( a3 == 3.1415 );
	FIXEDPOINT_TESTER( a3 != 3.1414 );

	FIXEDPOINT_TESTER( 3.1416 > a3 );
	FIXEDPOINT_TESTER( 3.1414 < a3 );
	FIXEDPOINT_TESTER( 3.1416 >= a3 );
	FIXEDPOINT_TESTER( 3.1414 <= a3 );
	FIXEDPOINT_TESTER( 3.1415 == a3 );
	FIXEDPOINT_TESTER( 3.1414 != a3 );
#endif

#if TESTLOGICAL
	float p = 3.14159265359f;
	float e = 2.71828182846f;

	int x = 10;
	int y = 2;

	fixed16_t fa = 10;
	fixed16_t fb = 2;

	fixed16_t fp = p;
	fixed16_t fe = e;

	std::cout << "==================================================" << std::endl;
	std::cout << "==   LOGICAL  ==" << std::endl;
	std::cout << "==================================================" << std::endl;

	FIXEDPOINT_TESTER( ( p && e)  == ( fp && fe ) );
	FIXEDPOINT_TESTER( ( p || e)  == ( fp || fe ) );
	FIXEDPOINT_TESTER( ( x & y )  == ( fa & fb ) );
	FIXEDPOINT_TESTER( ( x | y )  == ( fa | fb ) );
	FIXEDPOINT_TESTER( ( x ^ y )  == ( fa ^ fb ) );
	FIXEDPOINT_TESTER( ( ~x )  == ( ~fa ) );
	FIXEDPOINT_TESTER( ( fa >> 2 ).toInt() == ( x >> 2 ) );
	FIXEDPOINT_TESTER( ( fa << 2 ).toInt() == ( x << 2 ) );
#endif

#if TESTTRIG
	float w = 0.523598776f;
	fixed16_t a = w;
	fixed24_t b = w;

	std::cout << "==================================================" << std::endl;
	std::cout << "==   TRIG  ==" << std::endl;
	std::cout << "==================================================" << std::endl;
	
	fixed16_t sn = fixed16_t::fixed_sine(a);
	fixed16_t cs = fixed16_t::fixed_cosine(a);

	FIXEDPOINT_TESTER( ( nearlyEqual( sin(w), sn.toFloat(), EPSIL )) == true );
	FIXEDPOINT_TESTER( ( nearlyEqual( cos(w), cs.toFloat(), EPSIL )) == true );
#endif


	std::cout << "==================================================" << std::endl;
	std::cout << "==   OUTPUT WITH COUT  ==" << std::endl;
	std::cout << "==================================================" << std::endl;

	std::cout << "Fixed PI: " << fp << std::endl;
	std::cout << "Fixed e: " << fe << std::endl;
}

bool nearlyEqual(float a, float b, float epsilon) 
{
	float absA = abs(a);
	float absB = abs(b);
	float diff = abs(a - b);

	if (a == b) 
	{ 
		// shortcut, handles infinities
		return true;
	} 
	else if (a == 0 || b == 0 || diff < FLT_MIN ) 
	{
		// a or b is zero or both are extremely close to it
		// relative error is less meaningful here
		return diff < (epsilon * FLT_MIN );
	} 
	else 
	{ 
		// use relative error
		return diff / (absA + absB) < epsilon;
	}
}

int main()
{	
	TestsFixed();

	std::cin.get();
	return 0;
}