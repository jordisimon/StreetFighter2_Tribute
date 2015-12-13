#pragma once

class Config;

class Service
{
public:
	Service() {};
	virtual ~Service() {};

	virtual bool Init(const Config& config) { return true; }
	virtual bool CleanUp() { return true; }

	virtual bool Start() { return true; }
	virtual bool Stop() { return true; }
};

