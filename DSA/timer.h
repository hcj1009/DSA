#ifndef TIMER_H
#define TIMER_H

#include <chrono>

namespace DSA
{
    namespace utility
    {
        class timer {
            typedef double rep;
            typedef std::chrono::steady_clock clock;
            typedef std::chrono::duration<rep> duration;
        private:
            clock::time_point m_start;
        public:
            explicit timer(const bool &run = false) { if (run) reset(); }
            void reset() { m_start = clock::now(); }
            rep elapsed() const
            {
                return (std::chrono::duration_cast<duration>
                    (clock::now() - m_start)).count();
            }
        };
    }
}

#endif