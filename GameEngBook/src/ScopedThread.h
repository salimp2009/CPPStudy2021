#pragma once

/* custom assert with message; void is used to supress Unused warnings!*/
#define	ASSERTM(exp, msg) assert(((void)msg, exp))

class scopedThread
{
private: 
	std::thread m_t;
public:
	explicit scopedThread(std::thread t): m_t{std::move(t)} 
	{
		ASSERTM(m_t.joinable(), "no  threads");
	}

	~scopedThread() { m_t.join(); }

	scopedThread(const scopedThread&) = delete;
	scopedThread& operator=(const scopedThread&) = delete;

};
