#pragma once

class Config;

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

	virtual bool Init(const Config& config) { return true; }
	virtual bool CleanUp() { return true; }

	virtual bool Start() { return true; }
	virtual bool Stop() { return true; }

	virtual Result ProcessInput() { return Result::R_OK; };
	virtual Result UpdateState() { return Result::R_OK; };
	virtual Result Draw() { return Result::R_OK; };
};

