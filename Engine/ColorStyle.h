#pragma once

#include "Colors.h"
#include "Random.h"

class ColorStyle
{
public:
	ColorStyle()
		:
		ColorStyle( Colors::Magenta,0,false )
	{}
	ColorStyle( Color base,int dev,bool mono = false )
		:
		baseCol( base ),
		deviation( dev ),
		monochrome( mono )
	{}

	Color Generate() const
	{
		Color temp;
		if( monochrome )
		{
			const auto amount = int( Random{ -deviation,deviation } );
			temp = Colors::MakeRGB(
				int( baseCol.GetR() ) + amount,
				int( baseCol.GetG() ) + amount,
				int( baseCol.GetB() ) + amount
			);
		}
		else
		{
			temp = Colors::MakeRGB(
				int( baseCol.GetR() ) + int( Random{ -deviation,deviation } ),
				int( baseCol.GetG() ) + int( Random{ -deviation,deviation } ),
				int( baseCol.GetB() ) + int( Random{ -deviation,deviation } )
			);
		}

		return( temp );
	}
public:
	Color baseCol;
	int deviation;
	bool monochrome = false;
};