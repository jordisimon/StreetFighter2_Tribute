#pragma once

struct CommandData;

class Entity
{
public:
	enum class Result
	{
		R_OK = 1,
		R_EXIT,
		R_ERROR
	};

	Entity() {};
	virtual ~Entity() {};

	virtual bool Init() { return true; }
	virtual bool CleanUp() { return true; }

	virtual bool Start() { return true; }
	virtual bool Stop() { return true; }

	virtual bool ProcessInput(CommandData* commandData) { return true; };
	virtual Result UpdateState() { return Result::R_OK; };
	virtual Result Draw() const { return Result::R_OK; };
};

