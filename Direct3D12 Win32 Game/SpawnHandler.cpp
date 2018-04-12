#include "pch.h"
#include "SpawnHandler.h"
#include "Events.h"
#include "RenderData.h"

SpawnHandler::~SpawnHandler()
{
	int del_count = m_delete_queue.size();
	if (del_count)
	{
		for (int i = 0; i < del_count; i++)
		{
			if(m_delete_queue[i])
			delete m_delete_queue[i];
		}
		m_delete_queue.clear();
	}
}

void SpawnHandler::onNotify(GameObject2D * object, Event _event)
{
	switch (_event)
	{
	case Event::OBJECT_INSTANTIATED:
	{
		m_2DObjects->push_back(object);
		m_physics->push_back(object->GetPhysics());
		break;
	}
	case Event::OBJECT_DESTROYED:
	case Event::PLAYER_ELIMINATED:
	{
		m_RD->m_resourceCount--;
		int i = 0;
		for (std::vector<GameObject2D*>::iterator it = m_2DObjects->begin();
			it != m_2DObjects->end(); it++, i++)
		{
			if (*it == object)
			{
				m_2DObjects->erase(m_2DObjects->begin() + i);
				break;
			}
		}
		i = 0;
		for (std::vector<Physics2D*>::iterator it = m_physics->begin();
			it != m_physics->end(); it++, i++)
		{
			if (*it == object->GetPhysics())
			{
				m_physics->erase(m_physics->begin() + i);
				break;
			}
		}
		//after deleting the mine, it was removed from all vectors 
		//before its "collision exit" could be called 
		//because of that the Character thought it is still colliding with it
		//thus I had to force the removal when removing it from vector

		//loop trought the whole vector remove the physics of the deleted object from all other physics
		for (std::vector<Physics2D*>::iterator it = m_physics->begin();
			it != m_physics->end(); it++, i++)
		{
			(*m_physics)[i]->removeFromCurrentlyColliding(object->GetPhysics());
		}

		m_delete_queue.push_back(object);
		break;
	}
	}
}

void SpawnHandler::setData(std::vector<GameObject2D*>* _2DObjects,
	std::vector<Physics2D*>* _physics, RenderData* _RD)
{
	m_RD = _RD;
	m_2DObjects = _2DObjects;
	m_physics = _physics;
}
