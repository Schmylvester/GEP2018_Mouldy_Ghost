#include "pch.h"
#include "TestScene.h"
#include "RenderData.h"
#include "GameStateData.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

void TestScene::Initialise(RenderData * _RD,
	GameStateData * _GSD, int _outputWidth,
	int _outputHeight,
	std::unique_ptr<DirectX::AudioEngine>& _audEngine)
{
	m_RD = _RD;
	m_GSD = _GSD;

	//GEP::This is where I am creating the test objects
	m_cam = new Camera(static_cast<float>(_outputWidth),
		static_cast<float>(_outputHeight), 1.0f, 1000.0f);
	m_RD->m_cam = m_cam;
	m_3DObjects.push_back(m_cam);

	TestPBGO3D* test3d = new TestPBGO3D();
	test3d->SetScale(5.0f);
	test3d->Init();
	m_3DObjects.push_back(test3d);

	Text2D * test2 = new Text2D("I am a test scene");
	m_2DObjects.push_back(test2);

	TestSound* TS = new TestSound(_audEngine.get(), "Explo1");
	m_sounds.push_back(TS);
}

void TestScene::Reset()
{
	for (int i = 0; i < m_GSD->objects_in_scene.size(); i++)
	{
		m_GSD->objects_in_scene[i]->ResetForce(BOTH_AXES);
	}
	for (int i = 0; i < m_2DObjects.size(); i++)
	{
		m_2DObjects[i]->ResetPos();
	}

	for (int i = 0; i < m_3DObjects.size(); i++)
	{
		m_3DObjects[i]->ResetPos();
	}
}