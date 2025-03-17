#pragma once

#include <vector>

template<typename T>
class Transition;

template<typename T>
class Action
{
	std::vector<Transition<T>*> m_transitions;

private:
    int Update(T* _pOwner);

public:
    ~Action();

    Transition<T>* CreateTransition(int _state);

protected:
	virtual void OnStart(T* _pOwner) = 0;
	virtual void OnUpdate(T* _pOwner) = 0;
	virtual void OnEnd(T* _pOwner) = 0;

	template<typename T>
	friend class StateMachine;
};

#include "Action.inl"