#ifndef TIMERS_H
#define TIMERS_H

class Timer
{
public:
    Timer(unsigned long intervalMs);
    
    ~Tick();

    bool ShouldExecute() const;
    
    void Tick( unsigned long elaspedMs );
};


#endif
