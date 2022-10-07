#pragma once
#include <string>
#include <vector>
#include <functional>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include "xorstr.hpp"
#include "sdk.h"
#include "menu.h"
using namespace std;


static int gameMode = 0;
static int gameMode2 = 0;

#define MAX_RGB 255.0
#define HELPMARKERDESC(str) ImGui::SameLine(); ImGui::TextColored(ImColor(0, 130, 15, 255), "[ ? ]"); if (ImGui::IsItemHovered()) ImGui::SetTooltip(str)
#define HELPMARKERDISC(str) ImGui::SameLine(); ImGui::TextColored(ImColor(0, 130, 15, 255), "[ * ]"); if (ImGui::IsItemHovered()) ImGui::SetTooltip(str)
#pragma warning(disable: 26812 26815)

float color_menu[4]{ 196 / 255.f, 87 / 255.f , 218 / 255.f, 1.0f };
char customtag[5] = "";

const char CWAether[29] = "camo_zm_t9mastery_darkmatter";
const char CWUltra[30] = "camo_mp_t9mastery_darkmatter";
const char CWGold[24] = "camo_mp_t9mastery_gold";
const char CWDiamond[27] = "camo_mp_t9mastery_diamond";
const char CWPDiamond[27] = "camo_zm_t9mastery_diamond";
const char CW_Reset[19] = "camo_mp_t9tier1_01";
const char Cherry[19] = "camo_mp_t9tier5_05";

const char Damascus[9] = "camo_11c";
const char Obisidian[9] = "camo_11d";
const char Gold[12] = "camo_11a";
const char MW_Reset[9] = "camo_01a";
const char MW_Diamond[9] = "camo_11b";

const char VGGold[12] = "s4_camo_11a";
const char VGDiamond[12] = "s4_camo_11b";
const char VGAtomic[12] = "s4_camo_11c";
const char VGGoldenViper[15] = "s4_camo_11a_zm";
const char VGPlagueDiamond[15] = "s4_camo_11b_zm";
const char VGDarkAether[15] = "s4_camo_11c_zm";
const char VG_Reset[12] = "s4_camo_01a";
const char ZM_Reset[128] = "s4_camo_01a_zm";

char score[256] = "";
char games[256] = "";
char timeplayed[256] = "";
char wins[256] = "";
char top5[256] = "";
char kills[256] = "";
char deaths[256] = "";
char downs[256] = "";

void SetCamo(int Class, int Weapon, int Camo)
{
	char context[255];
	char state[255];
	int navStringCount;
	char* navStrings[16]{};
	const char* mode = "";

	if (gameMode == 0)
	{
		mode = xorstr_("ddl/mp/rankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 3);
	}
	else if (gameMode == 1)
	{
		mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 5);
	}



	__int64 ddl_file = Com_DDL_LoadAsset((__int64)mode);

	DDL_GetRootState((__int64)state, ddl_file);
	char buffer[200];
	memset(buffer, 0, 200);
	sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.weaponSetups.%i.camo"), Class, Weapon);
	ParseShit(buffer, (const char**)navStrings, 16, &navStringCount);
	if (DDL_MoveToPath((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
	{
		DDL_SetInt((__int64)state, (__int64)context, Camo);
	}

}

void CopyWeapon(int Class)
{
	char context[255];
	char state[255];
	char context2[255];
	char state2[255];
	int navStringCount;
	char* navStrings[16]{};
	int navStringCount2;
	char* navStrings2[16]{};
	const char* mode = "";
	int wep = 0;
	if (gameMode2 == 0)
	{
		mode = xorstr_("ddl/mp/rankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 3);
	}
	else if (gameMode2 == 1)
	{
		mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context, 0, 0, 5);
	}



	__int64 ddl_file = Com_DDL_LoadAsset((__int64)mode);

	DDL_GetRootState((__int64)state, ddl_file);
	char buffer[200];
	memset(buffer, 0, 200);
	sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.weaponSetups.0.weapon"), Class);
	ParseShit(buffer, (const char**)navStrings, 16, &navStringCount);
	if (DDL_MoveToPath((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
	{
		wep = DDL_GetInt((__int64*)&state, (__int64*)&context);

	}
	if (gameMode2 == 0)
	{
		mode = xorstr_("ddl/mp/rankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context2, 0, 0, 3);
	}
	else if (gameMode2 == 1)
	{
		mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
		CL_PlayerData_GetDDLBuffer((__int64)context2, 0, 0, 5);
	}
	__int64 ddl_file2 = Com_DDL_LoadAsset((__int64)mode);
	DDL_GetRootState((__int64)state2, ddl_file2);
	char buffer2[200];
	memset(buffer2, 0, 200);
	sprintf_s(buffer2, xorstr_("squadMembers.loadouts.%i.weaponSetups.1.weapon"), Class);
	ParseShit(buffer2, (const char**)navStrings2, 16, &navStringCount2);
	if (DDL_MoveToPath((__int64*)&state2, (__int64*)&state2, navStringCount2, (const char**)navStrings2))
	{
		DDL_SetInt2((__int64*)&state2, (__int64*)&context2, wep);
	}


}

namespace Tabs
{
	int iTab = 0;
	bool bExit = false;
};

namespace NJUI
{

	void Line(int newId)
	{
		std::string id = ("ImGui_Sauce_line_" + std::to_string(newId));
		ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
		{
			ImGui::BeginChild(id.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 1), false);
			ImGui::Separator();
			ImGui::EndChild();
		}
		ImGui::PopStyleColor();
	}

	void Linevertical()
	{
		ImGui::SameLine();
		ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
		ImGui::SameLine();
	}

	void CenterText(const char* text, int lineId, bool separator)
	{
		if (text == nullptr)
			return;

		ImGui::Spacing();
		ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (ImGui::CalcTextSize(text).x / 2));
		ImGui::Text(text);
		ImGui::Spacing();

		if (true == separator)
			Line(lineId);
	}

	void CenterTextEx(const char* text, float width, int lineId, bool separator)
	{
		if (text == nullptr)
			return;

		ImGui::Spacing();
		ImGui::SameLine((width / 2) - (ImGui::CalcTextSize(text).x / 2));
		ImGui::Text(text);
		ImGui::Spacing();

		if (true == separator)
			Line(lineId);
	}

	void Colors()
	{
		static float rainbow;
		rainbow += 0.0030f; //0.0001f
		if (rainbow > 1.f)
			rainbow = 0.f;

		auto rgb = ImColor::HSV(rainbow, 1.f, 1.f, 0.8f);     // Rainbow Items
		auto rgb_a = ImColor::HSV(rainbow, 1.f, 1.f, 0.9f);   // Selected / Hovered Items
		auto rgb_b = ImColor::HSV(rainbow, 1.f, 1.f, 0.7f);   // Pressed Items

		ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float | ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_PickerHueWheel);
		ImGuiStyle* Style = &ImGui::GetStyle();
		Style->WindowBorderSize = 4;
		Style->FrameBorderSize = 0;
		Style->WindowRounding = 4;
		Style->ChildRounding = 4;
		Style->ChildBorderSize = 4;
		Style->FrameRounding = 4;
		Style->ScrollbarSize = 0;
		Style->WindowPadding = ImVec2(0, 0);
		Style->FramePadding = ImVec2(0, 0);
		Style->IndentSpacing = 0;
		Style->DisplayWindowPadding = ImVec2(0, 0);
		Style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
		Style->Colors[ImGuiCol_Border] = rgb;
		Style->Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
		Style->Colors[ImGuiCol_FrameBg] = ImColor(40, 40, 40, 255);
		Style->Colors[ImGuiCol_FrameBgHovered] = ImColor(40, 40, 40, 255);
		Style->Colors[ImGuiCol_FrameBgActive] = ImColor(40, 40, 40, 255);
		Style->Colors[ImGuiCol_SliderGrab] = ImColor(255, 255, 255);
		Style->Colors[ImGuiCol_SliderGrabActive] = ImColor(255, 255, 255);
		Style->Colors[ImGuiCol_Button] = rgb;
		Style->Colors[ImGuiCol_CheckMark] = rgb;
	}
}
