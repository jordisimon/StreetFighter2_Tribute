#pragma once

class Collider;

class ICollitionListener
{
public:
	virtual void OnCollitionEnter(Collider* colA, Collider* colB) = 0;
	virtual void OnCollitionExit(Collider* colA, Collider* colB) = 0;
};
