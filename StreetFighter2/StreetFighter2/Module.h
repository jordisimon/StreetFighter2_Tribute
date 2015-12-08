#pragma once
#include "Config.h"

class Module
{
private:
	bool m_active = true;

public:
	enum class Update_result
	{
		UPDATE_OK = 1,
		UPDATE_EXIT, 
		UPDATE_ERROR
	};

	Module(bool active = true) :
		m_active{ active }
	{}

	virtual ~Module() {}

	bool IsEnabled() const { return m_active; }
	bool Enable()
	{
		if (!m_active)
			return m_active = Start();

		return true;
	}

	bool Disable()
	{
		if (m_active)
			return m_active = Stop();

		return true;
	}

	virtual bool Init(const Config& config) { return true; }
	virtual bool CleanUp() { return true; }

	virtual bool Start() { return true; }
	virtual bool Stop() { return true; }

	virtual Update_result PreUpdate() { return Update_result::UPDATE_OK; }
	virtual Update_result Update() { return Update_result::UPDATE_OK; }
	virtual Update_result PostUpdate() { return Update_result::UPDATE_OK; }
};

