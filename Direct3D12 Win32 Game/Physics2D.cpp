#include "pch.h"
#include "Physics2D.h"
#include "GameStateData.h"


Physics2D::Physics2D(RenderData* _RD, string _filename):ImageGO2D(_RD,_filename)
{
}


Physics2D::~Physics2D()
{
}

void Physics2D::ResetForce(Axis _axis)
{
	switch(_axis)
	{
	case X:
		m_vel.x = 0;
		m_acc.x = 0;
		break;
	case Y:
		m_vel.y = 0;
		m_acc.y = 0;
		break;
	case BOTH:
		m_vel.x = 0;
		m_vel.y = 0;
		m_acc.x = 0;
		m_acc.y = 0;
		break;
	default:
		break;
	}
}

//GEP:: Basic Euler Solver for point mass 
void Physics2D::Tick(GameStateData * _GSD)
{
	//VERY Basic idea of drag i.e. the faster I go the more I get pulled back
	m_acc -= m_drag * m_vel;

	Vector2 newPos = m_pos + _GSD->m_dt * m_vel;
	Vector2 newVel = m_vel + _GSD->m_dt * m_acc;

	newVel.y += m_gravity_scale * m_gravity;

	m_pos = newPos;
	m_vel = newVel;
	m_acc = Vector2::Zero;

	//check for collisions
	for (int i = 0; i < _GSD->objects_in_scene.size(); i++)
	{
		Physics2D* object = _GSD->objects_in_scene[i];
		if (object != this)
		{
			Vector2 normal;
			if (m_bounding_rect->IsColliding(object->GetRectangle(), normal))
			{
				Collision(object);

				bool on_list = false;
				for (int j = 0; j < currently_colliding.size(); j++)
				{
					if (currently_colliding[j] == object)
					{
						on_list = true;
					}
				}
				if (!on_list)
				{
					currently_colliding.push_back(object);
					CollisionEnter(object, normal);
				}
			}
			else
			{
				for (int j = 0; j < currently_colliding.size(); j++)
				{
					if (currently_colliding[j] == object)
					{
						CollisionExit(object);
						currently_colliding.erase(currently_colliding.begin() + j);
					}
				}
			}
		}
	}
}

bool Physics2D::isColliding(Physics2D* _object, Vector2 &_normal)
{
	return m_bounding_rect->IsColliding(_object->GetRectangle(), _normal);
}

void Physics2D::CollisionEnter(Physics2D * _collision, Vector2 _normal)
{
	AddForce(_collision->GetVel() * _collision->GetMass() * 100);
}

void Physics2D::Collision(Physics2D * _collision)
{
}

void Physics2D::CollisionExit(Physics2D * _collision)
{
}
