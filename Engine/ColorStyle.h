#pragma once

#include "Colors.h"
#include "Random.h"
#include "Vec2.h"

class ColorStyle
{
public:
	constexpr ColorStyle()
		:
		ColorStyle( Colors::Magenta,0,false )
	{}
	constexpr ColorStyle( Color base,int dev,bool mono = false )
		:
		baseCol( base ),
		deviation( dev ),
		monochrome( mono )
	{}

	Color Generate() const
	{
		// Color temp;
		int tempR;
		int tempG;
		int tempB;
		if( monochrome )
		{
			const auto amount = int( Random{ -deviation,deviation } );
			// temp = Colors::MakeRGB(
			// 	int( baseCol.GetR() ) + amount,
			// 	int( baseCol.GetG() ) + amount,
			// 	int( baseCol.GetB() ) + amount
			// );
			tempR = baseCol.GetR() + amount;
			tempG = baseCol.GetG() + amount;
			tempB = baseCol.GetB() + amount;
		}
		else
		{
			// temp = Colors::MakeRGB(
			// 	int( baseCol.GetR() ) + int( Random{ -deviation,deviation } ),
			// 	int( baseCol.GetG() ) + int( Random{ -deviation,deviation } ),
			// 	int( baseCol.GetB() ) + int( Random{ -deviation,deviation } )
			// );
			tempR = baseCol.GetR() + int( Random{ -deviation,deviation } );
			tempG = baseCol.GetG() + int( Random{ -deviation,deviation } );
			tempB = baseCol.GetB() + int( Random{ -deviation,deviation } );
		}

		if( tempR < 0 ) tempR = 0;
		if( tempR > 255 ) tempR = 255;
		if( tempG < 0 ) tempG = 0;
		if( tempG > 255 ) tempG = 255;
		if( tempB < 0 ) tempB = 0;
		if( tempB > 255 ) tempB = 255;

		return( Colors::MakeRGB( tempR,tempG,tempB ) );
	}
public:
	Color baseCol;
	int deviation;
	bool monochrome = false;
};