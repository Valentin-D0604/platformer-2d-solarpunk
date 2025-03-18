#pragma once

#include <vector>

template<typename T>
class Condition;

template<typename T>
class Transition
{
protected:
    std::vector<Condition<T>*> m_conditions;
	int m_transitionState;

public:
	Transition(int _transitionState) : m_transitionState(_transitionState) {}

	template<typename U>
	U* AddCondition(bool _expected = true);
	
	bool Try(T* _owner);
	int GetTransitionState() { return m_transitionState; }
};

#include "Transition.inl"