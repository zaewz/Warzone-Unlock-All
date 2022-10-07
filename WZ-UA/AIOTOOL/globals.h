#pragma once
#ifndef GLOBAL_H
#define GLOBAL_H
#include "framework.h"

typedef struct _settings
{

	bool b_menuEnable = true;
	bool b_debugEnable = true;
	bool b_map = false;
	bool b_fov = false;
	bool b_heart = false;
	bool b_unlock = false;
	bool b_tut = false;
	bool b_fps = false;
	bool b_priv = false;
	bool b_no_flashbang = false;
	bool b_custom_clantag = false;
	bool b_brightmax = false;
	float f_fov = 1.2f;
	float f_map = 1.0f;
	bool b_Thirdperson = false;
	bool b_sThirdperson = false;
	bool b_sprint = false;
	bool b_test = false;
	bool b_shield = false;
	bool b_no_fog = false;
	bool b_gun = false;
	bool b_no_stun = false;
	bool b_owner = false;
	float testing = 0.1f;
	bool b_testing = false;
	bool b_fuckview = false;
	int i_score = 1; //1 ~ 5555555555
	int i_timeplayed = 1;
	int i_games = 1; //1 ~ 5555555555
	int i_wins = 1; //1 ~ 5555555555
	int i_kills = 1; //1 ~ 5555555555
	int i_deaths = 1; //1 ~ 5555555555
	int i_downs = 1; //1 ~ 5555555555;
	int i_top5 = 1; //1 ~ 5555555555
	int i_top10 = 1; //1 ~ 5555555555
	int i_top25 = 1; //1 ~ 5555555555
	bool b_name = false;
	bool b_no_hud = false;
	bool b_crosshair = false;
	bool chrosshair = false;
	bool b_dynamic3p = false;
	bool b_recoil = false;

} settings;

typedef struct _offsets
{
	uintptr_t gamemode;
	uintptr_t camoAddr; //= 0x1A7C7918 + 0x28;
	uintptr_t mwcamoAddr;
	uintptr_t perkAddr1;
	uintptr_t perkAddr2;
	uintptr_t perkAddr3;
	uintptr_t cwcamoAddr;
	uintptr_t vgcamoAddr;
	uintptr_t clantag_offset;
	uintptr_t a_parse;
	uintptr_t unlock_offsets;
	uintptr_t Dvar_FindVarByName;
	uintptr_t Dvar_SetBoolInternal;
	uintptr_t Dvar_SetBoolByName;
	uintptr_t Dvar_SetFloat_Internal;
	uintptr_t Dvar_RegisterFloat;
	uintptr_t Dvar_SetInt_Internal;
	uintptr_t Dvar_SetIntByName;
	//stats
	uintptr_t ddl_loadasset;
	uintptr_t ddl_getrootstate;
	uintptr_t ddl_getdllbuffer;
	uintptr_t ddl_movetoname;
	uintptr_t ddl_movetopath;
	uintptr_t ddl_setint;
	uintptr_t ddl_getint;
	uintptr_t ddl_setstring;
	uintptr_t Logon_Status;
} offsets;

typedef struct Cached
{
	uintptr_t local_ptr;
	uintptr_t player_ptr;
	uint64_t cached_character_ptr;
	uint64_t cached_base_ptr;
	uint64_t cached_entity_ptr;
	uint64_t inputptr;
	uint64_t entity_ptr;
	QWORD current_visible_offset;
	QWORD cached_visible_base;
	QWORD last_visible_offset;
	int local_team_id;
	int player_team_id;
	uint32_t local_index;
	bool b_is_localalive;
	bool b_is_playeralive;

} Cached;

typedef struct _global_vars
{
	DWORD procID;
	HWND hWind;
	HANDLE hProc;
	uintptr_t baseModule;
	uint64_t moduleBase;
	offsets goffsets;
	settings msettings;
	Cached gCached;

} global_vars;

extern global_vars* g_vars;

#endif // !GLOBAL_H

