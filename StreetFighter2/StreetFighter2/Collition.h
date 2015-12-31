#pragma once

class Collider;

class Collition
{
private:
	const Collider* colA = nullptr;
	const Collider* colB = nullptr;

public:
	Collition(const Collider* cA, const Collider* cB);
	~Collition();

	bool HasCollider(const Collider* col) const;
	bool HasToDeleteCollider() const;
};

