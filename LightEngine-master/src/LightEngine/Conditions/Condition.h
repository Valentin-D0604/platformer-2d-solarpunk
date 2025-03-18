#pragma once

template <typename T>
class Transition;

template<typename T>
class Condition 
{
    bool Test(T* _owner);

public:
    bool expected = true;

    virtual bool OnTest(T* _owner) = 0;

    friend Transition<T>;
};

#include "Condition.inl"
