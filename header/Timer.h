#ifndef TIMER_H_
#define TIMER_H_

#include <set>
#include <boost/noncopyable.hpp>
#include "Units.h"

class Timer : private boost::noncopyable
{
public:
	Timer(units::MS expiration_time) :
		current_time_(expiration_time + 1),
		expiration_time_(expiration_time) 
	{
		timers_.insert(this);
	}

	~Timer() { timers_.erase(this); }

	bool reset() { return current_time_  = 0; }
	bool active() const { return current_time_ < expiration_time_; }
	bool expired() const { return !active(); }
	// Assumes the user knows if it is active or not.
	units::MS currentTime() const { return current_time_; }

	static void updateAll(units::MS elapsed_time);
private:
	void update(units::MS elapsed_time)
	{
		if (active())
		{
			current_time_ += elapsed_time;
		}
	}

	units::MS current_time_;
	const units::MS expiration_time_;

	static std::set<Timer*> timers_;
};

#endif // !TIMER_H_
