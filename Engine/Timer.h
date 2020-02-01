#pragma once

class Timer
{
public:
	Timer( float time )
		:
		maxTime( time )
	{}

	bool Update( float dt )
	{
		if( curTime <= maxTime ) curTime += dt;

		return( IsDone() );
	}

	void Reset()
	{
		curTime = 0.0f;
	}
	void Reset2()
	{
		curTime -= maxTime;
	}

	bool IsDone() const
	{
		return( curTime >= maxTime );
	}
	float GetPercent() const
	{
		return( std::min( 1.0f,curTime / maxTime ) );
	}
private:
	float maxTime;
	float curTime = 0.0f;
};