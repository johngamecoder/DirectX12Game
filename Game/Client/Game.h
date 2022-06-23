#pragma once

class Scene;

class Game
{
public:

	void Init(const WindowInfo& info);
	void Update();

private:
	shared_ptr<Scene> SolarSystemScene();
	shared_ptr<Scene> LoadTestScene();
};

