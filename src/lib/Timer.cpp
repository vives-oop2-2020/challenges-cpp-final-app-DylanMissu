#include "Timer.h"
#include <chrono>

Timer::Timer()
{
    millieSeconds = currentMillis();
    currentState = true;
}

int Timer::currentMillis()
{
    //https://stackoverflow.com/questions/19555121/how-to-get-current-timestamp-in-milliseconds-since-1970-just-the-way-java-gets
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}

int Timer::getElapsedMillis()
{
    return (int)(currentMillis() - millieSeconds);
}

void Timer::resetTimer()
{
    millieSeconds = currentMillis();
}

void Timer::setState(bool state)
{
    currentState = state;
}

bool Timer::getState()
{
    return currentState;
}

bool Timer::interval(int milliseconds)
{
    if (getElapsedMillis() > milliseconds)
    {
        resetTimer();
        return true;
    }
    else
    {
        return false;
    }
}