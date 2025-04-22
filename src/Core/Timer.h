#ifndef TIMER_H
#define TIMER_H
#include <list>
#include <functional>
namespace Core {

class Timer
{
	const unsigned intervalMs;
	const std::function<void()> handler;
public:
	Timer(unsigned long intervalMs, std::function<void()> handler);

	bool ShouldExecute() const;

	void Tick( unsigned long elaspedMs );

	unsigned long GetTfDeltaMs(unsigned long currentMs);

	void TickTimerFlags();

	bool ShouldExecute(short tfAttribute);

	void ResetTimerFlags();
};
}

#endif // TIMER_H
