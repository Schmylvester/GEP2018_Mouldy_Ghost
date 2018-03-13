#pragma once

const float m_gravity = 9.8f;

enum Axis
{
	X_AXIS,
	Y_AXIS,
	BOTH_AXES
};

//GEP:: Euler Integration Solve for VERY Basic 2D physics
class Physics2D
{
public:
	Physics2D();
	~Physics2D();

	void AddForce(Vector2 _push) { m_acc += _push / m_mass; }
	void ResetForce(Axis _axis);

	Vector2 GetVel() { return m_vel; }

	void SetMass(float _mass) { m_mass = _mass; }
	float GetMass() { return m_mass; }
	void SetDrag(float _drag) { m_drag = _drag; }
	float GetDrag() { return m_drag; }
	void SetBounce(float _bounce) { m_bounciness = _bounce; }
	const float GetBounce() { return m_bounciness; }
	void SetGrav(float _grav) { m_gravity_scale = _grav; }
	const float GetGrav() { return m_gravity_scale; }
	void SetOwner(GameObject2D* _owner) { owner = _owner; }
	GameObject2D* GetOwner() { return owner; }

	virtual void Tick(GameStateData* _GSD, Vector2& _pos);
	
	void SetCollider(Rectangle _collider){ m_collider = _collider; }
	Rectangle GetCollider() { return m_collider; }
	void MoveCollider(Vector2 _pos) {m_collider.Offset(_pos.x, _pos.y);}

#if _DEBUG
	void RenderCorners();
#endif;

protected:
	GameObject2D* owner = nullptr;

	Rectangle m_collider;
	std::vector<Physics2D*> currently_colliding;

	void CheckForCollisions(GameStateData * _GSD, Vector2& _pos);
	Vector2 GetNormal(Vector2 _point);

	Vector2 m_vel;
	Vector2 m_acc;

	float m_mass = 1.0f;
	float m_drag = 0.0f;

	float m_gravity_scale;
	float m_bounciness;
};