/*!
    \file critical_section.h
    \brief Critical section synchronization primitive definition
    \author Ivan Shynkarenka
    \date 27.01.2016
    \copyright MIT License
*/

#ifndef CPPCOMMON_THREADS_CRITICAL_SECTION_H
#define CPPCOMMON_THREADS_CRITICAL_SECTION_H

#include <memory>

namespace CppCommon {

//! Critical section synchronization primitive
/*!
    Critical sections prevents code fragments from access by multiple threads simultaneously. Only one thread can
    access the code inside the critical section. Other threads must wait for the lock! Critical sections are usually
    more lightweight than mutexes and don't enter kernel mode.

    Thread-safe.

    https://en.wikipedia.org/wiki/Critical_section
*/
class CriticalSection
{
public:
    CriticalSection();
    CriticalSection(const CriticalSection&) = delete;
    CriticalSection(CriticalSection&&) = default;
    ~CriticalSection();

    CriticalSection& operator=(const CriticalSection&) = delete;
    CriticalSection& operator=(CriticalSection&&) = default;

    //! Try to acquire critical section without block
    /*!
        Will not block.

        \return 'true' if the critical section was successfully acquired, 'false' if the critical section is busy
    */
    bool TryLock();

    //! Try to acquire critical section for the given spin count
    /*!
        Will block for the given spin count in the worst case.

        \param spin - Spin count
        \return 'true' if the critical section was successfully acquired, 'false' if the critical section is busy
    */
    bool TryLockSpin(int64_t spin);

    //! Acquire critical section with block
    /*!
        Will block.
    */
    void lock();

    //! Release critical section
    /*!
        Will not block.
    */
    void unlock();

private:
    class Impl;
    std::unique_ptr<Impl> _pimpl;
};

/*! \example threads_critical_section.cpp Critical section synchronization primitive example */

} // namespace CppCommon

#include "critical_section.inl"

#endif // CPPCOMMON_THREADS_CRITICAL_SECTION_H
