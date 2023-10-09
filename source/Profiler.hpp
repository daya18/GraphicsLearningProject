#pragma once

class Profiler
{
public:
	struct FrameMetrics
	{
		unsigned int fpsMean		{ 0 };
		unsigned int frameCount		{ 0 };
		float frameTimeMax			{ 0 };
		float frameTimeMin			{ 0 };
		float frameTimeMean			{ 0 };
	};

	Profiler ();

	void BeginFrame ();
	void EndFrame ();

	void SetSampleDurationMs ( float );
		
	float GetLastFrameDuration ();

	FrameMetrics const & GetFrameMetrics ();

private:
	using Clock = std::chrono::steady_clock;

	float CountMs ( Clock::duration );

	float sampleDurationMs { 1000 };
	std::vector <float> frameTimeSamples;
	Clock::time_point lastFrameBeginTime;
	Clock::time_point firstSampleBeginTime;
	FrameMetrics frameMetrics;
};

inline Profiler::FrameMetrics const & Profiler::GetFrameMetrics () { return frameMetrics; }
