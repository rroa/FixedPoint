#pragma once

#ifndef _FIXED_POINT_H_
#define _FIXED_POINT_H_

#define M_PI 3.14159265358979323846
#define _90degsInRadians 1.57079633 // 90 degrees in radians
#define EXTRA_PRECISION

#include <stdint.h>

template< int EXP >
struct FixedPoint
{
	typedef FixedPoint self;
public:
	/* =============================================================
	* CTOR
	* ============================================================= */
	FixedPoint( ) 
		: m_container( 0 ) 
	{}

	FixedPoint( int intValue ) 
		: m_container( static_cast< int >( intValue * factor )) 
	{}

	FixedPoint( double doubleValue ) 
		: m_container( static_cast< int >( doubleValue * factor )) 
	{}

	FixedPoint( float floatValue )  
		: m_container( static_cast< int >( floatValue * factor )) 
	{}

	/* =============================================================
	* ARITHMETIC OPERATORS
	* ============================================================= */

	/* ADDITION */	 
	self operator+ ( const self& rhs )
	{
		self result;
		result.m_container = m_container + rhs.m_container;
		return result;
	}

	self& operator+=( const self& rhs ) 
	{ 
		m_container += rhs.m_container; 
		return *this; 
	}

	/* SUBSTRACTION */	 
	self operator- ( const self& rhs )
	{
		self result;
		result.m_container = m_container - rhs.m_container;
		return result;
	}

	self& operator-=( const self& rhs ) 
	{ 
		m_container -= rhs.m_container; 
		return *this; 
	}

	/* MULTIPLICATION */	 
	self operator* ( const self& rhs )
	{
		self result;

		result.m_container = 
			(int)(((long long) m_container * (long long)rhs.m_container ) >> EXP );

		return result;
	}

	self& operator*=( const self& rhs ) 
	{ 
		m_container = 
			(int)(((long long) m_container * (long long)rhs.m_container ) >> EXP );

		return *this; 
	}

	self& operator*=( int rhs ) 
	{ 
		m_container *= rhs; 
		return *this; 
	}

	/* DIVIDE */	 
	self operator/ ( const self& rhs )
	{
		self result;
		result.m_container = 
			int( (((long long) m_container << (EXP * 2)) / (long long) rhs.m_container ) >> EXP );

		return result;
	}

	self& operator/=( const self& rhs ) 
	{ 
		m_container =
			int( (((long long) m_container << (EXP * 2)) / (long long) rhs.m_container ) >> EXP );

		return *this; 
	}	

	self& operator/=( int rhs ) 
	{ 
		m_container /= rhs; 
		return *this; 
	}

	self operator%( int rhs ) 
	{ 
		self result;
		result.m_container = ( ( m_container >> EXP ) % rhs ) << EXP; 
		return result;
	}

	self& operator%=( int rhs ) 
	{ 
		m_container = ( ( m_container >> EXP ) % rhs ) << EXP; 
		return *this;
	}

	/* =============================================================
	* UNARY OPERATORS
	* ============================================================= */
	self operator+ ()
	{		
		self result;
		result.m_container = ( m_container );
		return result;
	}

	self operator- ()
	{		
		self result;
		result.m_container = ( -m_container );
		return result;
	}
	
	bool operator! ()
	{
		return !m_container;
	}

	/* =============================================================
	* COMPARISON OPERATORS
	* ============================================================= */

	/* COMPARISONS AGAINST FIXED POINTS */
	bool operator==( const self& rhs )
	{
		return m_container == rhs.m_container;
	}

	bool operator!=( const self& rhs )
	{
		return m_container != rhs.m_container;
	}

	bool operator>( const self& rhs )
	{
		return m_container > rhs.m_container;
	}

	bool operator>=( const self& rhs )
	{
		return m_container >= rhs.m_container;
	}

	bool operator<( const self& rhs )
	{
		return m_container < rhs.m_container;
	}

	bool operator<=( const self& rhs )
	{
		return m_container <= rhs.m_container;
	}

	/* =============================================================
	* LOGICAL OPERATORS / BITWISE OPERATORS
	* ============================================================= */
	self operator~ () 
	{
		self result = ~(m_container >> EXP);
		return result;
	}

	bool operator&&( const self& rhs )
	{
		return ( m_container != 0 ) && ( rhs.m_container != 0 );
	}

	bool operator||( const self& rhs )
	{
		return ( m_container != 0 ) || ( rhs.m_container != 0 );
	}

	self operator&( const self& rhs )
	{
		self result;
		result.m_container = m_container & rhs.m_container;
		return result;
	}

	self& operator&=( const self& rhs )
	{
		m_container = m_container & rhs.m_container;
		return *this;
	}

	self operator|( const self& rhs )
	{
		self result;
		result.m_container = m_container | rhs.m_container;
		return result;
	}

	self& operator|=( const self& rhs )
	{
		m_container = m_container | rhs.m_container;
		return *this;
	}

	self operator^( const self& rhs )
	{
		self result;
		result.m_container = m_container ^ rhs.m_container;
		return result;
	}

	self& operator^=( const self& rhs )
	{
		m_container = m_container ^ rhs.m_container;
		return *this;
	}

	self& operator<<=( const int& shift )
	{
		m_container = m_container << shift;
		return *this;
	}

	self& operator>>=( const int& shift )
	{
		m_container = m_container >> shift;
		return *this;
	}

	/* =============================================================
	* TYPE CONVERSIONS
	* ============================================================= */
	operator float() 
	{ 
		return toFloat();
	}

	float toFloat( ) const 
	{ 		
		return float( m_container ) / factor;
	}

	operator double() 
	{ 
		return toDouble();
	}

	double toDouble( ) const 
	{ 
		return double( m_container ) / factor; 
	}

	operator int() 
	{ 
		return ( m_container >> EXP ); 
	}

	int toInt() const
	{
		return ( m_container >> EXP );
	}

	operator long() 
	{ 
		return ( m_container >> EXP ); 
	}

	/* =============================================================
	* FRIENDS
	* ============================================================= */
	friend std::ostream& operator<<( std::ostream& output, const FixedPoint& fixedPoint )
	{
		return output << fixedPoint.toDouble();
	}	

	friend FixedPoint operator<<( const FixedPoint& number, const int& shift )
	{
		FixedPoint result;
		result.m_container = number.m_container << shift;
		return result;
	}

	friend FixedPoint operator>>( const FixedPoint& number, const int& shift )
	{
		FixedPoint result;
		result.m_container = number.m_container >> shift;
		return result;
	}

	/* =============================================================
	* STATIC
	* ============================================================= */
	static self fixed_abs( const self& value )
	{
		self result = value;
		result.abs();
		return result;
	}

	static self fixed_sine( const self& inAngle )
	{
		self B = ( float( 4 ) / M_PI );		
		self C = ( float( -4 ) /( M_PI * M_PI ));

		self y = B * inAngle + C * inAngle * fixed_abs( inAngle );

#ifdef EXTRA_PRECISION
		//  const float Q = 0.775;
		self P = 0.225f;	
		y = P * ( y * fixed_abs( y ) - y ) + y;
#endif
		return y;
	}

	static self fixed_cosine( const self& inAngle )
	{		
		self _90degs = _90degsInRadians;
		return fixed_sine(( _90degs - inAngle ));
	}
private:
	static const int factor = 1 << ( EXP );	

	/* =============================================================
	* FUNCTIONS
	* ============================================================= */
	void abs()
	{
		if( m_container < 0 )
			m_container = -m_container;
	}

	/* =============================================================
	* MEMBERS
	* ============================================================= */
	int m_container;	
};

typedef FixedPoint<16> fixed16_t;
typedef FixedPoint<8> fixed24_t;

/* =============================================================
* INTS
* ============================================================= */
/* ARITHMETIC */
// Q.16
inline fixed16_t operator +( const int& lhs, const fixed16_t& rhs ) { return fixed16_t( lhs ) + rhs; }
inline fixed16_t operator +( fixed16_t& lhs, const int& rhs ) { return lhs + fixed16_t( rhs ); }
inline fixed16_t operator -( const int& lhs, const fixed16_t& rhs ) { return fixed16_t( lhs ) - rhs; }
inline fixed16_t operator -( fixed16_t& lhs, const int& rhs ) { return lhs - fixed16_t( lhs ); }
inline fixed16_t operator *( const int& lhs, const fixed16_t& rhs ) { return fixed16_t( lhs ) * rhs; }
inline fixed16_t operator *( fixed16_t& lhs, const int& rhs ) { return lhs * fixed16_t( rhs ); }
inline fixed16_t operator /( const int& lhs, const fixed16_t& rhs ) { return fixed16_t( lhs ) / rhs; }
inline fixed16_t operator /( fixed16_t& lhs, const int& rhs ) { return lhs / fixed16_t( rhs ); }

// Q.8
inline fixed24_t operator +( const int& lhs, const fixed24_t& rhs ) { return fixed24_t( lhs ) + rhs; }
inline fixed24_t operator +( fixed24_t& lhs, const int& rhs ) { return lhs + fixed24_t( rhs ); }
inline fixed24_t operator -( const int& lhs, const fixed24_t& rhs ) { return fixed24_t( lhs ) - rhs; }
inline fixed24_t operator -( fixed24_t& lhs, const int& rhs ) { return lhs - fixed24_t( lhs ); }
inline fixed24_t operator *( const int& lhs, const fixed24_t& rhs ) { return fixed24_t( lhs ) * rhs; }
inline fixed24_t operator *( fixed24_t& lhs, const int& rhs ) { return lhs * fixed24_t( rhs ); }
inline fixed24_t operator /( const int& lhs, const fixed24_t& rhs ) { return fixed24_t( lhs ) / rhs; }
inline fixed24_t operator /( fixed24_t& lhs, const int& rhs ) { return lhs / fixed24_t( rhs ); }

/* COMPARISONS */
// Q.16
inline bool operator==( fixed16_t lhs, const int& rhs ) { return lhs == fixed16_t( rhs ); }
inline bool operator==( const int& lhs, fixed16_t rhs  ) { return fixed16_t( lhs ) == rhs; }
inline bool operator!=( fixed16_t lhs, const int& rhs ) { return lhs != fixed16_t( rhs ); }
inline bool operator!=( const int& lhs, fixed16_t rhs  ) { return fixed16_t( lhs ) != rhs; }
inline bool operator<=( fixed16_t lhs, const int& rhs ) { return lhs <= fixed16_t( rhs ); }
inline bool operator<=( const int& lhs, fixed16_t rhs  ) { return fixed16_t( lhs ) <= rhs; }
inline bool operator>=( fixed16_t lhs, const int& rhs ) { return lhs >= fixed16_t( rhs ); }
inline bool operator>=( const int& lhs, fixed16_t rhs  ) { return fixed16_t( lhs ) >= rhs; }
inline bool operator>( fixed16_t lhs, const int& rhs ) { return lhs > fixed16_t( rhs ); }
inline bool operator>( const int& lhs, fixed16_t rhs  ) { return fixed16_t( lhs ) > rhs; }
inline bool operator<( fixed16_t lhs, const int& rhs ) { return lhs < fixed16_t( rhs ); }
inline bool operator<( const int& lhs, fixed16_t rhs  ) { return fixed16_t( lhs ) < rhs; }

// Q.8
inline bool operator==( fixed24_t lhs, const int& rhs ) { return lhs == fixed24_t( rhs ); }
inline bool operator==( const int& lhs, fixed24_t rhs  ) { return fixed24_t( lhs ) == rhs; }
inline bool operator!=( fixed24_t lhs, const int& rhs ) { return lhs != fixed24_t( rhs ); }
inline bool operator!=( const int& lhs, fixed24_t rhs  ) { return fixed24_t( lhs ) != rhs; }
inline bool operator<=( fixed24_t lhs, const int& rhs ) { return lhs <= fixed24_t( rhs ); }
inline bool operator<=( const int& lhs, fixed24_t rhs  ) { return fixed24_t( lhs ) <= rhs; }
inline bool operator>=( fixed24_t lhs, const int& rhs ) { return lhs >= fixed24_t( rhs ); }
inline bool operator>=( const int& lhs, fixed24_t rhs  ) { return fixed24_t( lhs ) >= rhs; }
inline bool operator>( fixed24_t lhs, const int& rhs ) { return lhs > fixed24_t( rhs ); }
inline bool operator>( const int& lhs, fixed24_t rhs  ) { return fixed24_t( lhs ) > rhs; }
inline bool operator<( fixed24_t lhs, const int& rhs ) { return lhs < fixed24_t( rhs ); }
inline bool operator<( const int& lhs, fixed24_t rhs  ) { return fixed24_t( lhs ) < rhs; }

/* =============================================================
* FLOATS
* ============================================================= */
/* ARITHMETIC */
// Q.16
inline fixed16_t operator +( const float& lhs, const fixed16_t& rhs ) { return fixed16_t( lhs ) + rhs; }
inline fixed16_t operator +( fixed16_t& lhs, const float& rhs ) { return lhs + fixed16_t( rhs ); }
inline fixed16_t operator -( const float& lhs, const fixed16_t& rhs ) { return fixed16_t( lhs ) - rhs; }
inline fixed16_t operator -( fixed16_t& lhs, const float& rhs ) { return lhs - fixed16_t( lhs ); }
inline fixed16_t operator *( const float& lhs, const fixed16_t& rhs ) { return fixed16_t( lhs ) * rhs; }
inline fixed16_t operator *( fixed16_t& lhs, const float& rhs ) { return lhs * fixed16_t( rhs ); }
inline fixed16_t operator /( const float& lhs, const fixed16_t& rhs ) { return fixed16_t( lhs ) / rhs; }
inline fixed16_t operator /( fixed16_t& lhs, const float& rhs ) { return lhs / fixed16_t( rhs ); }

// Q.8
inline fixed24_t operator +( const float& lhs, const fixed24_t& rhs ) { return fixed24_t( lhs ) + rhs; }
inline fixed24_t operator +( fixed24_t& lhs, const float& rhs ) { return lhs + fixed24_t( rhs ); }
inline fixed24_t operator -( const float& lhs, const fixed24_t& rhs ) { return fixed24_t( lhs ) - rhs; }
inline fixed24_t operator -( fixed24_t& lhs, const float& rhs ) { return lhs - fixed24_t( lhs ); }
inline fixed24_t operator *( const float& lhs, const fixed24_t& rhs ) { return fixed24_t( lhs ) * rhs; }
inline fixed24_t operator *( fixed24_t& lhs, const float& rhs ) { return lhs * fixed24_t( rhs ); }
inline fixed24_t operator /( const float& lhs, const fixed24_t& rhs ) { return fixed24_t( lhs ) / rhs; }
inline fixed24_t operator /( fixed24_t& lhs, const float& rhs ) { return lhs / fixed24_t( rhs ); }

/* COMPARISONS */
// Q.16
inline bool operator==( fixed16_t lhs, const float& rhs ) { return lhs == fixed16_t( rhs ); }
inline bool operator==( const float& lhs, fixed16_t rhs  ) { return fixed16_t( lhs ) == rhs; }
inline bool operator!=( fixed16_t lhs, const float& rhs ) { return lhs != fixed16_t( rhs ); }
inline bool operator!=( const float& lhs, fixed16_t rhs  ) { return fixed16_t( lhs ) != rhs; }
inline bool operator<=( fixed16_t lhs, const float& rhs ) { return lhs <= fixed16_t( rhs ); }
inline bool operator<=( const float& lhs, fixed16_t rhs  ) { return fixed16_t( lhs ) <= rhs; }
inline bool operator>=( fixed16_t lhs, const float& rhs ) { return lhs >= fixed16_t( rhs ); }
inline bool operator>=( const float& lhs, fixed16_t rhs  ) { return fixed16_t( lhs ) >= rhs; }
inline bool operator>( fixed16_t lhs, const float& rhs ) { return lhs > fixed16_t( rhs ); }
inline bool operator>( const float& lhs, fixed16_t rhs  ) { return fixed16_t( lhs ) > rhs; }
inline bool operator<( fixed16_t lhs, const float& rhs ) { return lhs < fixed16_t( rhs ); }
inline bool operator<( const float& lhs, fixed16_t rhs  ) { return fixed16_t( lhs ) < rhs; }

// Q.8
inline bool operator==( fixed24_t lhs, const float& rhs ) { return lhs == fixed24_t( rhs ); }
inline bool operator==( const float& lhs, fixed24_t rhs  ) { return fixed24_t( lhs ) == rhs; }
inline bool operator!=( fixed24_t lhs, const float& rhs ) { return lhs != fixed24_t( rhs ); }
inline bool operator!=( const float& lhs, fixed24_t rhs  ) { return fixed24_t( lhs ) != rhs; }
inline bool operator<=( fixed24_t lhs, const float& rhs ) { return lhs <= fixed24_t( rhs ); }
inline bool operator<=( const float& lhs, fixed24_t rhs  ) { return fixed24_t( lhs ) <= rhs; }
inline bool operator>=( fixed24_t lhs, const float& rhs ) { return lhs >= fixed24_t( rhs ); }
inline bool operator>=( const float& lhs, fixed24_t rhs  ) { return fixed24_t( lhs ) >= rhs; }
inline bool operator>( fixed24_t lhs, const float& rhs ) { return lhs > fixed24_t( rhs ); }
inline bool operator>( const float& lhs, fixed24_t rhs  ) { return fixed24_t( lhs ) > rhs; }
inline bool operator<( fixed24_t lhs, const float& rhs ) { return lhs < fixed24_t( rhs ); }
inline bool operator<( const float& lhs, fixed24_t rhs  ) { return fixed24_t( lhs ) < rhs; }

/* =============================================================
* DOUBLES
* ============================================================= */
/* ARITHMETIC */
// Q.16
inline fixed16_t operator +( const double& lhs, const fixed16_t& rhs ) { return fixed16_t( lhs ) + rhs; }
inline fixed16_t operator +( fixed16_t& lhs, const double& rhs ) { return lhs + fixed16_t( rhs ); }
inline fixed16_t operator -( const double& lhs, const fixed16_t& rhs ) { return fixed16_t( lhs ) - rhs; }
inline fixed16_t operator -( fixed16_t& lhs, const double& rhs ) { return lhs - fixed16_t( lhs ); }
inline fixed16_t operator *( const double& lhs, const fixed16_t& rhs ) { return fixed16_t( lhs ) * rhs; }
inline fixed16_t operator *( fixed16_t& lhs, const double& rhs ) { return lhs * fixed16_t( rhs ); }
inline fixed16_t operator /( const double& lhs, const fixed16_t& rhs ) { return fixed16_t( lhs ) / rhs; }
inline fixed16_t operator /( fixed16_t& lhs, const double& rhs ) { return lhs / fixed16_t( rhs ); }

// Q.8
inline fixed24_t operator +( const double& lhs, const fixed24_t& rhs ) { return fixed24_t( lhs ) + rhs; }
inline fixed24_t operator +( fixed24_t& lhs, const double& rhs ) { return lhs + fixed24_t( rhs ); }
inline fixed24_t operator -( const double& lhs, const fixed24_t& rhs ) { return fixed24_t( lhs ) - rhs; }
inline fixed24_t operator -( fixed24_t& lhs, const double& rhs ) { return lhs - fixed24_t( lhs ); }
inline fixed24_t operator *( const double& lhs, const fixed24_t& rhs ) { return fixed24_t( lhs ) * rhs; }
inline fixed24_t operator *( fixed24_t& lhs, const double& rhs ) { return lhs * fixed24_t( rhs ); }
inline fixed24_t operator /( const double& lhs, const fixed24_t& rhs ) { return fixed24_t( lhs ) / rhs; }
inline fixed24_t operator /( fixed24_t& lhs, const double& rhs ) { return lhs / fixed24_t( rhs ); }

/* COMPARISONS */
// Q.16
inline bool operator==( fixed16_t lhs, const double& rhs ) { return lhs == fixed16_t( rhs ); }
inline bool operator==( const double& lhs, fixed16_t rhs  ) { return fixed16_t( lhs ) == rhs; }
inline bool operator!=( fixed16_t lhs, const double& rhs ) { return lhs != fixed16_t( rhs ); }
inline bool operator!=( const double& lhs, fixed16_t rhs  ) { return fixed16_t( lhs ) != rhs; }
inline bool operator<=( fixed16_t lhs, const double& rhs ) { return lhs <= fixed16_t( rhs ); }
inline bool operator<=( const double& lhs, fixed16_t rhs  ) { return fixed16_t( lhs ) <= rhs; }
inline bool operator>=( fixed16_t lhs, const double& rhs ) { return lhs >= fixed16_t( rhs ); }
inline bool operator>=( const double& lhs, fixed16_t rhs  ) { return fixed16_t( lhs ) >= rhs; }
inline bool operator>( fixed16_t lhs, const double& rhs ) { return lhs > fixed16_t( rhs ); }
inline bool operator>( const double& lhs, fixed16_t rhs  ) { return fixed16_t( lhs ) > rhs; }
inline bool operator<( fixed16_t lhs, const double& rhs ) { return lhs < fixed16_t( rhs ); }
inline bool operator<( const double& lhs, fixed16_t rhs  ) { return fixed16_t( lhs ) < rhs; }

// Q.8
inline bool operator==( fixed24_t lhs, const double& rhs ) { return lhs == fixed24_t( rhs ); }
inline bool operator==( const double& lhs, fixed24_t rhs  ) { return fixed24_t( lhs ) == rhs; }
inline bool operator!=( fixed24_t lhs, const double& rhs ) { return lhs != fixed24_t( rhs ); }
inline bool operator!=( const double& lhs, fixed24_t rhs  ) { return fixed24_t( lhs ) != rhs; }
inline bool operator<=( fixed24_t lhs, const double& rhs ) { return lhs <= fixed24_t( rhs ); }
inline bool operator<=( const double& lhs, fixed24_t rhs  ) { return fixed24_t( lhs ) <= rhs; }
inline bool operator>=( fixed24_t lhs, const double& rhs ) { return lhs >= fixed24_t( rhs ); }
inline bool operator>=( const double& lhs, fixed24_t rhs  ) { return fixed24_t( lhs ) >= rhs; }
inline bool operator>( fixed24_t lhs, const double& rhs ) { return lhs > fixed24_t( rhs ); }
inline bool operator>( const double& lhs, fixed24_t rhs  ) { return fixed24_t( lhs ) > rhs; }
inline bool operator<( fixed24_t lhs, const double& rhs ) { return lhs < fixed24_t( rhs ); }
inline bool operator<( const double& lhs, fixed24_t rhs  ) { return fixed24_t( lhs ) < rhs; }

#endif