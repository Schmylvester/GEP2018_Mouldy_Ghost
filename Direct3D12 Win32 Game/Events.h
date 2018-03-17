#pragma once

enum Event {
	GAME_OVER,
	PLAYER_COLLIDE,
	PLAYER_HIT,
	PLAYER_DEAD,
	PLAYER_SPAWN,
	PLAYER_MOVE,
	PLAYER_PICKUP_ITEM,
	CHANGE_SCENE,
	CHANGE_SCENE_MAIN_MENU,
	CHANGE_SCENE_TEST,
	CHANGE_SCENE_GAME,
	CHANGE_SCENE_PHYSICS,
	CHANGE_SCENE_CHARACTER_SELECT,
	CHANGE_SCENE_GAME_SETTINGS,
	PLAYER_SELECTED,
	AI_ADDED,
	GAME_PAUSED,
	APPLICATION_LOADED,
	GAME_START,
	OBJECT_INSTANTIATED,
	OBJECT_DESTROYED,
	GAME_SETTINGS_INCREASE_LIVES,
	GAME_SETTINGS_DECREASE_LIVES,
	GAME_SETTINGS_INCREASE_TIME,
	GAME_SETTINGS_DECREASE_TIME,
};