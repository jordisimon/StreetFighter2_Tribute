#include "ParticleAttack.h"



ParticleAttack::ParticleAttack(ParticleType typ, const fPoint& pos, Direction dir, SDL_Texture* text) : Particle(typ, pos, dir, text)
{
}


ParticleAttack::~ParticleAttack()
{
}
