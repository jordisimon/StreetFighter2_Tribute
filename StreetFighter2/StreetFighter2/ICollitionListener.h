#pragma once

class Collider;

class ICollitionListener
{
public:
	virtual ~ICollitionListener() {}

	virtual void OnCollitionEnter(Collider* colA, Collider* colB) = 0;
	virtual void OnCollitionExit(Collider* colA, Collider* colB) = 0;
};
