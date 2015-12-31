#include "Collition.h"
#include "Collider.h"

Collition::Collition(const Collider * cA, const Collider * cB): colA { cA }, colB { cB }	
{
	
}


Collition::~Collition()
{
}

bool Collition::HasCollider(const Collider * col) const
{
	return (col == colA) || (col == colB);
}

bool Collition::HasToDeleteCollider() const
{
	return (colA->toDelete) || (colB->toDelete);
}
