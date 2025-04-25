#ifndef TIMER_H
#define TIMER_H
#include <functional>

namespace Core
{

using milliseconds = uint32_t;

template<milliseconds IntervalMs>
class Timer
{
	using Handler = const std::function<void()>;
	using intervalMs = IntervalMs;

	milliseconds nextExecuteMs;

	Handler handler;

public:
	Timer( Handler handler, milliseconds nextExecuteMs = IntervalMs ) :
		handler( handler ), nextExecuteMs( nextExecuteMs )
	{}

	bool ShouldExecute( milliseconds currentMs ) const { return currentMs >= nextExecuteMs; }

	void ExecuteHandler() { handler(); }

	void Tick( const milliseconds currentMs )
	{
		if( ShouldExecute( currentMs ) )
		{
			ExecuteHandler();
			ResetTimer( currentMs );
		}
	}

	void ResetTimer( const milliseconds currentMs )
	{
		// May cause overflow (once every 49.7 days), but currentMs will overflow at the same time
		nextExecuteMs += intervalMs;
	}
};

milliseconds GetSysUptimeMs() const;

void InitTimerSystem();
}
}


#endif // TIMER_H
