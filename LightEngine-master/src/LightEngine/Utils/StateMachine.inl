#include "StateMachine.h"

#include "../Actions/Action.h"

template<typename T>
StateMachine<T>::StateMachine(T* owner, int stateCount)
{
	m_owner = owner;
	m_currentState = -1;
	m_actions.resize(stateCount);
}

template<typename T>
StateMachine<T>::~StateMachine()
{
	for (Action<T>* pAction : m_actions)
		delete pAction;
}

template<typename T>
void StateMachine<T>::SetState(int state)
{
	if (m_currentState > 0 && m_currentState < m_actions.size())
		m_actions[m_currentState]->OnEnd(m_owner);

	m_currentState = state;

	m_actions[m_currentState]->OnStart(m_owner);
}

template<typename T>
void StateMachine<T>::Update()
{
	if (m_currentState == -1)
		return;

	int transitionState = m_actions[m_currentState]->Update(m_owner);

	if (transitionState == -1)
		return;

	SetState(transitionState);
}

template<typename T>
template<typename U>
U* StateMachine<T>::CreateAction(int state)
{
	_ASSERT(state >= 0 && state < m_actions.size());
	_ASSERT(m_actions[state] == nullptr);

	static_assert(std::is_base_of<Action<T>, U>::value, "U must derive from Action<T>");

	U* pAction = new U();

	m_actions[state] = pAction;
	
	return pAction;
}