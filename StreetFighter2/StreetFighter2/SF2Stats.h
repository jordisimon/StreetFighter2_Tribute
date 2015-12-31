#pragma once
class SF2Stats
{
public:
	SF2Stats();
	~SF2Stats();

	static unsigned int initialRecord;

	static unsigned int currentRecord;

	static unsigned int p1Score;
	static unsigned int p1Victories;
	static unsigned int p1Draws;
	static unsigned int p1Defeats;

	static unsigned int p2Score;
	static unsigned int p2Victories;
	static unsigned int p2Draws;
	static unsigned int p2Defeats;
};

