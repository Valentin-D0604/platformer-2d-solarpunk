#pragma once

#include <vector>

#include "../Actions/Action.h"

template<typename T>
class StateMachine
{
	std::vector<Action<T>*> m_actions;
	int m_currentState;

	T* m_owner;

public:
	StateMachine(T* _owner, int _stateCount);
	~StateMachine();

	void Update();
	void SetState(int _state);
	int GetCurrentState() const { return m_currentState; }

	template<typename U>
	U* CreateAction(int _state);
};

#include "StateMachine.inl"

