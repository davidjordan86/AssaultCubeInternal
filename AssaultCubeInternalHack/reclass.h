#pragma once
#include "pch.h"

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

struct Vector3
{
	float x, y, z;
};

enum class PlayerState : int8_t
{
	CS_ALIVE = 0,
	CS_DEAD = 1,
	CS_EDITING = 4,
	CS_LAGGED = 3,
	CS_SPAWNING = 2,
	CS_SPECTATE = 5
};

class weapon
{
public:
	char pad_0004[16]; //0x0004
	class ammo* ammoPtr; //0x0014
	class ammo* clipPtr; //0x0018
}; //Size: 0x001C

// Created with ReClass.NET 1.2 by KN4CK3R
class playerent
{
public:

	// be sure to put all the offsets you pad this way in a union
	union
	{
		//              Type     Name    Offset
		DEFINE_MEMBER_N(Vector3, head_pos, 0x0004);

		DEFINE_MEMBER_N(Vector3, velocity, 0x0010);

		DEFINE_MEMBER_N(Vector3, direction, 0x0028);

		DEFINE_MEMBER_N(Vector3, position, 0x0034);

		DEFINE_MEMBER_N(Vector3, view_angles, 0x0040);

		DEFINE_MEMBER_N(float, max_speed, 0x0050);

		DEFINE_MEMBER_N(float, eye_height, 0x005C);

		DEFINE_MEMBER_N(int8_t, b_grounded, 0x0069);

		DEFINE_MEMBER_N(PlayerState, state, 0x0082);

		DEFINE_MEMBER_N(int32_t, health, 0x00F8);

		DEFINE_MEMBER_N(int32_t, armor, 0x00FC);

		DEFINE_MEMBER_N(int32_t, frags, 0x01FC);

		DEFINE_MEMBER_N(int32_t, deaths, 0x0204);

		DEFINE_MEMBER_N(int8_t, b_attacking, 0x0224);

		DEFINE_MEMBER_N(char, name, 0x0225);

		DEFINE_MEMBER_N(int32_t, team, 0x032C);

		DEFINE_MEMBER_N(weapon*, current_weapon_ptr, 0x0374);
	};
};


class entlist
{
public:
	char pad_0000[4]; //0x0000
	class botent* N00000602[32]; //0x0004
}; //Size: 0x0084

class botent
{
public:
	Vector3 HeadPos; //0x0004
	Vector3 Velocity; //0x0010
	char pad_001C[24]; //0x001C
	Vector3 Position; //0x0034
	Vector3 ViewAngle; //0x0040
	char pad_004C[28]; //0x004C
	int32_t bIsGrounded; //0x0068
	char pad_006C[140]; //0x006C
	int32_t Health; //0x00F8
	char pad_00FC[296]; //0x00FC
	int8_t bIsAttacking; //0x0224
	char Name[16]; //0x0225
	char pad_0235[123]; //0x0235
}; //Size: 0x02B0

class ammo
{
public:
	int32_t ammo; //0x0000
}; //Size: 0x0004
