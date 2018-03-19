#pragma once

enum OnHold
{
	HOLD_CHARGE,		//Changes the attack when the button is held
	HOLD_REPEAT,		//Repeats the attack until the button is released
	HOLD_NONE			//Attacks once and holding the button will make the player just stand there
};

enum Destroy
{
	ON_PLAYER_HIT,
	ON_ANYTHING_HIT,
	AFTER_TIME
};

class Character;
struct DamageColData
{
	Character * user;
	bool child_to_player;
	float time;
	float speed;
	Vector2 direction;
	Destroy contact;
	int damage;
	int knockback;
	Vector2 size;
	bool grav;
};