#ifndef CORE_TIMER_H
#define CORE_TIMER_H
#include <functional>

namespace Core
{
namespace Timer
{

using milliseconds = unsigned int;

milliseconds GetSysUptimeMs();

void InitTimerSystem();

class IntervalTimer
{
	using Handler = std::function<void()>;

	milliseconds nextExecuteMs;

	const milliseconds intervalMs;

	const Handler handler;

public:
	IntervalTimer( milliseconds IntervalMs, Handler handler );

	IntervalTimer( milliseconds IntervalMs, Handler handler, milliseconds nextExecuteMs );

	bool ShouldExecute( milliseconds currentMs ) const;

	void ExecuteHandler();

	void Tick( const milliseconds currentMs );

	void ResetTimer( const milliseconds currentMs );
};

} // namespace Timer
} // namespace Core


#endif // CORE_TIMER_H
