#include "ModuleParticles.h"
#include "Defines.h"

using namespace std;

bool ModuleParticles::CleanUp()
{
	for (list<Particle*>::iterator it = particles.begin(); it != particles.end(); ++it)
		RELEASE(*it);

	return true;
}
