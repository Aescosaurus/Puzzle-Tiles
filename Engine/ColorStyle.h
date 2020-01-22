#pragma once

#include "Colors.h"
#include "Random.h"
#include "Vec2.h"

class ColorStyle
{
public:
	ColorStyle()
		:
		ColorStyle( Colors::Magenta,0,false )
	{}
	ColorStyle( Color base,int dev,bool mono = false )
		:
		ColorStyle( base,dev,mono,Vei2::Zero(),0.0f )
	{}
	ColorStyle( Color base,int dev,bool mono,
		const Vei2& pos,float falloff )
		:
		baseCol( base ),
		deviation( dev ),
		monochrome( mono ),
		pos( pos ),
		fallOff( falloff )
	{}

	Color Generate( Vei2 pos = Vei2{ -1,-1 } ) const
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

		const auto brightnessVal = CalcBrightness( pos );
		temp = Colors::Interpolate( temp,Colors::Black,brightnessVal );

		return( temp );
	}

	float CalcBrightness( Vei2 pos ) const
	{
		float val = 0.0f;
		if( pos.x != -1 )
		{
			const auto diff = this->pos - pos;
			val = diff.GetLength() * fallOff;
		}
		if( val > 1.0f ) val = 1.0f;
		return( val );
	}
public:
	Color baseCol;
	int deviation;
	bool monochrome = false;
	Vei2 pos;
	float fallOff;
};