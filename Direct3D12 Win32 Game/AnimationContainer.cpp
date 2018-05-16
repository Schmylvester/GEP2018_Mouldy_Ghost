#include "pch.h"
#include "AnimationContainer.h"
#include "GameStateData.h"
#include "RenderData.h"

#include <jsoncons\json.hpp>
#include "Animation2D.h"

AnimationContainer::AnimationContainer(RenderData* _RD, string _filename)
	: ImageGO2D(_RD, _filename)
{
	m_origin = Vector2(0, 0);
}


void AnimationContainer::Tick(GameStateData * _GSD)
{

	if (usesAnimation)
	{
		active_anim->update(_GSD);
	}

	GameObject2D::Tick(_GSD);


}

void AnimationContainer::changeAnimation(int _direction)
{
	if (_direction > 0)
	{
		if (active_anim == idle_anim.get())
		{
			switchAnimation(run_anim.get());
		}
		else if (active_anim == run_anim.get())
		{
			switchAnimation(jump_anim.get());
		}
		else if (active_anim == jump_anim.get())
		{
			switchAnimation(attack_anim.get());
		}
		else if (active_anim == attack_anim.get())
		{
			switchAnimation(idle_anim.get());
		}
	}
	else
	{
		if (active_anim == idle_anim.get())
		{
			switchAnimation(attack_anim.get());
		}
		else if (active_anim == run_anim.get())
		{
			switchAnimation(idle_anim.get());
		}
		else if (active_anim == jump_anim.get())
		{
			switchAnimation(run_anim.get());
		}
		else if (active_anim == attack_anim.get())
		{
			switchAnimation(jump_anim.get());
		}
	}
}

void AnimationContainer::Render(RenderData * _RD, int _sprite, Vector2 _cam_pos, float _zoom)
{
	Rectangle rect;
	rect = Rectangle(0, 0, m_spriteSize.x, m_spriteSize.y);

	const RECT* r = &RECT(rect);

	Vector2 render_scale;
	render_scale = m_scale * _zoom;
	Vector2 distance_from_origin = m_pos - _cam_pos;
	distance_from_origin *= _zoom;

	Vector2 render_pos = ((2 * _zoom) * _cam_pos) + distance_from_origin;
	render_pos.x += m_spriteSize.x / 4;



	if (usesAnimation)
	{
		active_anim->Render(_RD, _cam_pos, _zoom, render_scale, m_pos, m_resourceNum, m_colour, m_orientation, m_origin, flipped);
	}
	else
	{
		if (!flipped)
		{
			_RD->m_spriteBatch->Draw(_RD->m_resourceDescriptors->GetGpuHandle(m_resourceNum),
				GetTextureSize(allTextures[m_textureIndex].texture.Get()),
				render_pos, r, m_colour, m_orientation, m_origin, render_scale);
		}
		else
		{
			_RD->m_spriteBatch->Draw(_RD->m_resourceDescriptors->GetGpuHandle(m_resourceNum),
				GetTextureSize(allTextures[m_textureIndex].texture.Get()),
				render_pos, r, m_colour, m_orientation, m_origin, render_scale, SpriteEffects::SpriteEffects_FlipHorizontally, 0);
		}
	}
}


void AnimationContainer::loadAnimations(std::string _file, RenderData* _RD)
{
	//load animations here
	usesAnimation = true;
	using jsoncons::json;

	std::string path = "..\\GameAssets\\Characters\\Animations\\" + _file + ".json";

	SetName(_file);
	std::ifstream
		is(path);

	json animations;
	is >> animations;

	Rectangle spritebox;

	for (const auto& type : animations.members())
	{
		const std::string name = type.name();
		const auto& data = type.value();

		if (name == "run")
		{
			run_anim = std::make_shared<Animation2D>(_RD, data["spritesheet"].as_string(), m_resourceNum);
			run_anim->setFilename(data["spritesheet"].as_string());
			run_anim->setFramerate(data["framerate"].as_long());
			run_anim->setIncrements(Vector2(data["xIncrements"].as_long(), data["yIncrements"].as_long()));
			spritebox = Rectangle(data["startX"].as_long(), data["startY"].as_long(), data["boxWidth"].as_long(), data["boxHeight"].as_long());
			run_anim->setSpriteBoxStartPos(Vector2(spritebox.x, spritebox.y));
			run_anim->setSpriteBox(spritebox);
			run_anim->setFurthestLeftPos(data["furthestLeftPos"].as_long());
			run_anim->setMaxFrames(data["frames"].as_int());
		}
		else if (name == "jump")
		{
			jump_anim = std::make_shared<Animation2D>(_RD, data["spritesheet"].as_string(), m_resourceNum);
			jump_anim->setFilename(data["spritesheet"].as_string());
			jump_anim->setFramerate(data["framerate"].as_long());
			jump_anim->setIncrements(Vector2(data["xIncrements"].as_long(), data["yIncrements"].as_long()));
			spritebox = Rectangle(data["startX"].as_long(), data["startY"].as_long(), data["boxWidth"].as_long(), data["boxHeight"].as_long());
			jump_anim->setSpriteBoxStartPos(Vector2(spritebox.x, spritebox.y));
			jump_anim->setSpriteBox(spritebox);
			jump_anim->setFurthestLeftPos(data["furthestLeftPos"].as_long());
			jump_anim->setMaxFrames(data["frames"].as_int());
		}
		else if (name == "idle")
		{
			idle_anim = std::make_shared<Animation2D>(_RD, data["spritesheet"].as_string(), m_resourceNum);
			idle_anim->setFilename(data["spritesheet"].as_string());
			idle_anim->setFramerate(data["framerate"].as_long());
			idle_anim->setIncrements(Vector2(data["xIncrements"].as_long(), data["yIncrements"].as_long()));
			spritebox = Rectangle(data["startX"].as_long(), data["startY"].as_long(), data["boxWidth"].as_long(), data["boxHeight"].as_long());
			idle_anim->setSpriteBoxStartPos(Vector2(spritebox.x, spritebox.y));
			idle_anim->setSpriteBox(spritebox);
			idle_anim->setFurthestLeftPos(data["furthestLeftPos"].as_long());
			idle_anim->setMaxFrames(data["frames"].as_int());
		}
		else if (name == "attack")
		{
			attack_anim = std::make_shared<Animation2D>(_RD, data["spritesheet"].as_string(), m_resourceNum);
			attack_anim->setFilename(data["spritesheet"].as_string());
			attack_anim->setFramerate(data["framerate"].as_long());
			attack_anim->setIncrements(Vector2(data["xIncrements"].as_long(), data["yIncrements"].as_long()));
			spritebox = Rectangle(data["startX"].as_long(), data["startY"].as_long(), data["boxWidth"].as_long(), data["boxHeight"].as_long());
			attack_anim->setSpriteBoxStartPos(Vector2(spritebox.x, spritebox.y));
			attack_anim->setSpriteBox(spritebox);
			attack_anim->setFurthestLeftPos(data["furthestLeftPos"].as_long());
			attack_anim->setMaxFrames(data["frames"].as_int());
		}
	}

	SetSpriteSize(Vector2(spritebox.width, spritebox.height), 0);
	m_origin = Vector2(float(spritebox.x / 2), float(spritebox.y / 2));
	switchAnimation(idle_anim.get());
}

void AnimationContainer::saveAnimations(std::string _file)
{
	using jsoncons::json;

	std::string path = "..\\GameAssets\\Characters\\Animations\\" + GetName() + ".json";


	std::ofstream
		is(path);

	json animations;
	animations["run"]["spritesheet"] = run_anim->getFilename();
	animations["run"]["framerate"] = run_anim->getFramerate();
	animations["run"]["frames"] = run_anim->getMaxFrames();
	animations["run"]["xIncrements"] = run_anim->getIncrements().x;
	animations["run"]["yIncrements"] = run_anim->getIncrements().y;
	animations["run"]["boxWidth"] = run_anim->getSpriteBox().width;
	animations["run"]["boxHeight"] = run_anim->getSpriteBox().height;
	animations["run"]["furthestLeftPos"] = run_anim->getFurthestLeftPos();
	animations["run"]["startX"] = run_anim->getSpriteboxStartPos().x;
	animations["run"]["startY"] = run_anim->getSpriteboxStartPos().y;

	animations["jump"]["spritesheet"] = jump_anim->getFilename();
	animations["jump"]["framerate"] = jump_anim->getFramerate();
	animations["jump"]["frames"] = jump_anim->getMaxFrames();
	animations["jump"]["xIncrements"] = jump_anim->getIncrements().x;
	animations["jump"]["yIncrements"] = jump_anim->getIncrements().y;
	animations["jump"]["boxWidth"] = jump_anim->getSpriteBox().width;
	animations["jump"]["boxHeight"] = jump_anim->getSpriteBox().height;
	animations["jump"]["furthestLeftPos"] = jump_anim->getFurthestLeftPos();
	animations["jump"]["startX"] = jump_anim->getSpriteboxStartPos().x;
	animations["jump"]["startY"] = jump_anim->getSpriteboxStartPos().y;

	animations["idle"]["spritesheet"] = idle_anim->getFilename();
	animations["idle"]["framerate"] = idle_anim->getFramerate();
	animations["idle"]["frames"] = idle_anim->getMaxFrames();
	animations["idle"]["xIncrements"] = idle_anim->getIncrements().x;
	animations["idle"]["yIncrements"] = idle_anim->getIncrements().y;
	animations["idle"]["boxWidth"] = idle_anim->getSpriteBox().width;
	animations["idle"]["boxHeight"] = idle_anim->getSpriteBox().height;
	animations["idle"]["furthestLeftPos"] = idle_anim->getFurthestLeftPos();
	animations["idle"]["startX"] = idle_anim->getSpriteboxStartPos().x;
	animations["idle"]["startY"] = idle_anim->getSpriteboxStartPos().y;

	animations["attack"]["spritesheet"] = attack_anim->getFilename();
	animations["attack"]["framerate"] = attack_anim->getFramerate();
	animations["attack"]["frames"] = attack_anim->getMaxFrames();
	animations["attack"]["xIncrements"] = attack_anim->getIncrements().x;
	animations["attack"]["yIncrements"] = attack_anim->getIncrements().y;
	animations["attack"]["boxWidth"] = attack_anim->getSpriteBox().width;
	animations["attack"]["boxHeight"] = attack_anim->getSpriteBox().height;
	animations["attack"]["furthestLeftPos"] = attack_anim->getFurthestLeftPos();
	animations["attack"]["startX"] = attack_anim->getSpriteboxStartPos().x;
	animations["attack"]["startY"] = attack_anim->getSpriteboxStartPos().y;
	is << animations;
}



void AnimationContainer::switchAnimation(Animation2D * _new)
{
	if (_new && _new != active_anim)
	{
		_new->reset();
		active_anim = _new;
	}
	else
	{
		OutputDebugString(L"ANIMATION NOT INITIALISED");
	}
}

void AnimationContainer::FlipX()
{
	flipped = !flipped;
}