#pragma once

#include "LevelObject.h"

// Basic gate requires you to shoot the trigger to open.
// The trigger is one block of this type with none surrounding it.
class BasicGate
	:
	public LevelObject
{
public:
	BasicGate( const Vei2& pos );
};