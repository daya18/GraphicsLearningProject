#include "Profiler.hpp"

Profiler::Profiler ()
{
	auto now { Clock::now () };

	lastFrameBeginTime = now;
	firstSampleBeginTime = now;
}

void Profiler::BeginFrame ()
{
	lastFrameBeginTime = Clock::now ();
}

void Profiler::EndFrame ()
{
	auto lastFrameEndTime { Clock::now () };

	auto lastFrameDuration { lastFrameEndTime - lastFrameBeginTime };
	auto lastFrameDurationMcs { std::chrono::duration_cast <std::chrono::microseconds> (lastFrameDuration).count () };
	auto lastFrameDurationMs { static_cast <float> ( lastFrameDurationMcs ) / 1000.0f };

	frameTimeSamples.push_back ( lastFrameDurationMs );

	auto sampleRuntime { CountMs ( lastFrameEndTime - firstSampleBeginTime ) };

	if ( sampleRuntime >= sampleDurationMs)
	{
		frameMetrics.frameCount = frameTimeSamples.size ();
		frameMetrics.fpsMean = glm::round ( ( frameMetrics.frameCount / sampleRuntime ) * 1000 );
		frameMetrics.frameTimeMax = *std::max_element ( frameTimeSamples.begin (), frameTimeSamples.end () );
			
		frameMetrics.frameTimeMean = std::accumulate ( frameTimeSamples.begin (), frameTimeSamples.end (), 0 ) 
			/ static_cast <float> ( frameTimeSamples.size () );

		frameTimeSamples.clear ();
		frameTimeSamples.reserve ( 5000 );

		firstSampleBeginTime = lastFrameEndTime;
	}
}

void Profiler::SetSampleDurationMs ( float duration )
{
	//sampleDurationMs = duration;
}

float Profiler::GetLastFrameDuration ()
{
	if ( frameTimeSamples.empty () )
		return 0.0f;

	return frameTimeSamples.back ();
}

float Profiler::CountMs ( Clock::duration duration )
{
	return std::chrono::duration_cast <std::chrono::milliseconds> (duration).count ();
}