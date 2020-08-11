/*
    _____               __  ___          __            ____        _      __
   / ___/__ ___ _  ___ /  |/  /__  ___  / /_____ __ __/ __/_______(_)__  / /_
  / (_ / _ `/  ' \/ -_) /|_/ / _ \/ _ \/  '_/ -_) // /\ \/ __/ __/ / _ \/ __/
  \___/\_,_/_/_/_/\__/_/  /_/\___/_//_/_/\_\\__/\_, /___/\__/_/ /_/ .__/\__/
                                               /___/             /_/
                                             
  See Copyright Notice in gmMachine.h

*/

#ifndef _GMITERATOR_H_
#define _GMITERATOR_H_

//
// Intrusive Container Iterator
//

//
// Iterator must declare the following functions
//
// void Inc()
// void Dec()
// T* Resolve()
// const T* Resolve() const
// bool IsValid() const
//

#define GM_INCLUDE_ITERATOR_KERNEL(T)                                \
GM_INLINEWII void operator++() { Inc(); }                                  \
GM_INLINEWII void operator--() { Dec(); }                                  \
GM_INLINEWII void operator++(int) { Inc(); }                               \
GM_INLINEWII void operator--(int) { Dec(); }                               \
GM_INLINEWII T& operator*(void) { return *Resolve(); }                     \
GM_INLINEWII const T& operator*(void) const { return *Resolve(); }         \
GM_INLINEWII T* operator->(void) { return Resolve(); }                     \
GM_INLINEWII const T* operator->(void) const { return Resolve(); }         \
                                                                     \
GM_INLINEWII operator bool(void) { return IsValid(); }                     \
GM_INLINEWII operator bool(void) const { return IsValid(); }               \
GM_INLINEWII bool operator !(void) { return !IsValid(); }                  \
GM_INLINEWII bool operator !(void) const { return !IsValid(); }            \
                                                                     \
private:                                                             \
GM_INLINEWII operator unsigned int(void) { return 0xDEADBEEF; }            \
GM_INLINEWII operator int(void) { return 0xDEADBEEF; }                     \
GM_INLINEWII operator unsigned int(void) const { return 0xDEADBEEF; }      \
GM_INLINEWII operator int(void) const { return 0xDEADBEEF; }               \
public:

#endif // _GMITERATOR_H_
