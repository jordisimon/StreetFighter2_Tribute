#include "ServiceFade.h"
#include "ServicesManager.h"
#include "ServiceTime.h"
#include "ServiceRender.h"
#include "Scene.h"


ServiceFade::ServiceFade() : startTime{ 0 }, totalTime{ 0 }, fadingOut{ true }, color{Color::Predefined::BLACK}
{
}


ServiceFade::~ServiceFade()
{
}

void ServiceFade::StartFading(Scene * in, Scene * out, float fadeTime)
{
	fadingOut = (out != nullptr) ? true : false;
	startTime = servicesManager->time->CurrentTime();

	if (fadingOut)
		totalTime = (unsigned int)(fadeTime * 500.0f); //Time splited between fade out and in
	else
		totalTime = (unsigned int)(fadeTime * 1000.0f); //Total time to fade out

	sceneIn = in;
	sceneOut = out;
}

void ServiceFade::Fade()
{
	if (startTime > 0)
	{
		unsigned int now = servicesManager->time->CurrentTime() - startTime;
		float normalized = (float)now / (float)totalTime;

		if (normalized > 1.0f)
			normalized = 1.0f;

		if (!fadingOut)
			normalized = 1.0f - normalized;

		color.alpha = (unsigned int)(normalized * 255.0f);
		servicesManager->render->SetDrawColor(color);
		servicesManager->render->FillScreen();

		//If only fading in, start scene
		if (sceneOut == nullptr && sceneIn != nullptr)
		{
			sceneIn->Start();
			sceneIn = nullptr;
		}

		//When fading completed
		if (now >= totalTime)
		{
			//If it was fading out, start fadin in
			if (fadingOut)
			{
				if (sceneOut != nullptr)
					sceneOut->Stop();

				sceneIn->Start();

				totalTime += totalTime;
				startTime = servicesManager->time->CurrentTime();
				fadingOut = false;
			}
			//we are done
			else
			{
				startTime = 0;
			}
		}
	}
}
