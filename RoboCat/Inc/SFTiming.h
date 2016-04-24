#pragma once

class SFTiming
{
public:

	SFTiming();

	void Update();

	float GetDeltaTime() const { return mDeltaTime; }

	double GetTime() const;

	float GetTimef() const
	{
		return static_cast< float >(GetTime());
	}

	float GetFrameStartTime() const { return mFrameStartTimef; }


	static SFTiming sInstance;

private:
	float		mDeltaTime;
	uint64_t	mDeltaTick;

	double		mLastFrameStartTime;
	float		mFrameStartTimef;
	double		mPerfCountDuration;

};
