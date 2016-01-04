#pragma once
#include "ICollitionListener.h"
#include "Point.h"
#include "AnimationCollider.h"
#include "Direction.h"

struct SDL_Texture;
class Collider;
enum class ParticleType;   //To be defined in Game specific implementation

class Particle : public ICollitionListener
{
protected:
	ParticleType type;
	SDL_Texture* texture = nullptr;
	AnimationCollider* currentAnimation = nullptr;
	Direction direction;

public:
	fPoint position;
	bool toDelete;

	Particle(ParticleType typ, const fPoint& pos, Direction dir, SDL_Texture* text);
	virtual ~Particle();

	virtual bool UpdateState() { return true; };
	virtual bool Draw() const;

	void OnCollitionEnter(Collider* colA, Collider* colB) {};
	void OnCollitionExit(Collider* colA, Collider* colB) {};
};

