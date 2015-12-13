#pragma once
#include "Module.h"
#include <list>

class Particle;
struct SDL_Texture;

/*struct ParticleInfo
{
	Animation* anim;
	SDL_Texture* tex;
	fPoint pos;
	fPoint speed;

};*/

class ModuleParticles :	public Module
{
private:
	std::list<Particle*> particles;

public:
	ModuleParticles() {};
	~ModuleParticles() {};

	bool CleanUp();

	Module::Update_result Update();
	Module::Update_result PostUpdate();
};