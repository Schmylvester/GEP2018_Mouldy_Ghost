#pragma once
#include "Scene.h"
#include "Menu.h"

class GameSettingsScene :
	public Scene
{
public:
	GameSettingsScene();
	~GameSettingsScene();

	virtual std::string getType() override { return "GameSettings"; };

	virtual void Update(DX::StepTimer const & timer,
		std::unique_ptr<DirectX::AudioEngine>& _audEngine) override;
	virtual void Reset() override;
	virtual void Initialise(RenderData * _RD,
		GameStateData* _GSD, int _outputWidth,
		int _outputHeight, std::unique_ptr<DirectX::AudioEngine>& _audEngine);
private:
	std::shared_ptr<Menu> m_settingsMenu = nullptr;
};
