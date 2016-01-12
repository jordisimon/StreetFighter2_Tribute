#include "StageFactory.h"
#include "Stage.h"
#include "StageHonda.h"
#include "StageKen.h"
#include "StageGuile.h"


StageFactory::StageFactory()
{
}


StageFactory::~StageFactory()
{
}

Stage * StageFactory::CreateStage(StageType type)
{
	Stage* stage = nullptr;

	switch (type)
	{
	case StageType::RYU:
		break;
	case StageType::HONDA:
		stage = new StageHonda();
		break;
	case StageType::BLANKA:
		break;
	case StageType::GUILE:
		stage = new StageGuile();
		break;
	case StageType::KEN:
		stage = new StageKen();
		break;
	case StageType::CHUNLI:
		break;
	case StageType::ZANGUIEF:
		break;
	case StageType::DALSHIM:
		break;
	case StageType::BALROG:
		break;
	case StageType::VEGA:
		break;
	case StageType::SAGAT:
		break;
	case StageType::BISON:
		break;
	default:
		break;
	}

	return stage;
}
