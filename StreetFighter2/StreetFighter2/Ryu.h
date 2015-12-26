#pragma once
#include "Character.h"

class Ryu :	public Character
{
private:
	//Animation idle;
	//Animation idleBodyCol;
	//Animation fWalk;
	//Animation bWalk;
	//Animation jump;
	Animation fJump;
	Animation bJump;
	Animation crouch;
	Animation blocking;
	Animation cBlocking;
	Animation lPunch;
	Animation mPunch;
	Animation hPunch;
	Animation flPunch;
	Animation fmPunch;
	Animation fhPunch;
	Animation lKick;
	Animation mKick;
	Animation hKick;
	Animation flKick;
	Animation fmKick;
	Animation fhKick;
	Animation clPunch;
	Animation cmPunch;
	Animation chPunch;
	Animation clKick;
	Animation cmKick;
	Animation chKick;
	Animation jlPunch;
	Animation jmPunch;
	Animation jhPunch;
	Animation jlKick;
	Animation jmKick;
	Animation jhKick;
	Animation fjlPunch;
	Animation fjmPunch;
	Animation fjhPunch;
	Animation fjlKick;
	Animation fjmKick;
	Animation fjhKick;
	Animation shoryuken;
	Animation kyakuBegin;
	Animation kyaku;
	Animation kyakuEnd;
	Animation hadoken;
	Animation shoulderToss;
	Animation backRoll;
	Animation hit;
	Animation faceHit;
	Animation cHit;
	Animation knockdown;
	Animation knockdownRecover;
	Animation stunned;
	Animation KO;
	Animation victory1;
	Animation victory2;
	Animation timeover;

public:
	Ryu();
	~Ryu();

	bool Init();
};

