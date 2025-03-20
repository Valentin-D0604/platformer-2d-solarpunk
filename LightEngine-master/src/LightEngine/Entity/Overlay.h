#pragma once
#include "Entity.h"
class Overlay : public Entity
{
	Entity* m_player;
	float m_targetAlpha;
	float m_currentAlpha;
	float m_inDuration;
	float m_outDuration;
	bool m_nextOut;

public:
	void OnInitialize();
	void OnUpdate();
	void SetPlayer(Entity* _player);
	void FadeIn(float _duration);
	void FadeOut(float _duration);
	void FadeInOut(float _inDuration, float _outDuration);
};

