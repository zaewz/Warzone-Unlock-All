#include "menu.h"
#include "UI_Sauce.h"
#include "imguipp_v2.h"

ImFont* MainCaps;
ImFont* Main;
ImFont* FMenu;

std::string chars{ "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()`~-_=+[{]{|;:'\",<.>/?" };
std::random_device rd;
std::mt19937 generator(rd());
// Randomize String.
std::string RandStr(size_t length)
{
    const size_t char_size = chars.size();
    std::uniform_int_distribution<> random_int(0, char_size - 1);
    std::string output;
    for (size_t i = 0; i < length; ++i)
        output.push_back(chars[random_int(generator)]);
    return output;
}

std::string sRandWin = RandStr(12);
std::string sRandBegin = RandStr(12);
std::string sRandChild1 = RandStr(12);
std::string sRandChild2 = RandStr(12);
std::string sRandChild3 = RandStr(12);
std::string sRandChild4 = RandStr(12);
std::string sRandChild5 = RandStr(12);
ImVec2 screen_Size = ImVec2(WND_SIZEX, WND_SIZEY);


void AIO::MENUSHOW()
{
    NJUI::Colors();

    ImGui::SetNextWindowPos(ImVec2(screen_Size.x / 2.75, screen_Size.y / 2.75), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(240, 460), ImGuiCond_Always);

    if (ImGui::Begin(sRandBegin.c_str(), 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar))
    {

        ImGui::SetCursorPos(ImVec2(10, 10));
        if (ImGui::BeginChild(sRandChild2.c_str(), ImVec2(220, 440), true, ImGuiWindowFlags_NoDecoration))
        {
			ImGui::PushItemWidth(200);
            ImGui::Dummy(ImVec2(0.0f, 7.0f));

			ImGuiPP::CenterText("Sawr's MINI AIO", 1, TRUE);

            ImGui::Dummy(ImVec2(0.0f, 5.0f));

			ImGui::Indent(10);

			if (ImGui::Button(xorstr_("Unlock All"), ImVec2(200, 30)))
			{
				unlock();
			}

			ImGui::Unindent(10);
			//ImGui::TextDisabled(xorstr_(" Make sure you have the first camo equipped."));
			static const char* items[] = { "(MW) Gold", "(MW) Platinum", "(MW) Damascus", "(MW) Obsidian", "(CW) Gold", "(CW) Diamond", "(CW) DMU", "(CW) Golden Viper", "(CW) Plague Diamond", "(CW) Dark Aether", "(VG) Gold", "(VG) Diamond", "(VG) Atomic", "(VG) Fake Diamond", "(VG) Golden Viper", "(VG) Plague Diamond", "(VG) Dark Aether", "(CW) Cherry Blossom",  "(MW) Acticamo", "(MW) Banded", };
			static const char* current_item = "Select Camo";
			ImGuiPP::CenterText("Camo Editor", 1, TRUE);
			ImGui::Indent(10);
			static int item_current_2 = 0;
			ImGui::Combo("          ", &item_current_2, xorstr_("Class 1\0Class 2\0Class 3\0Class 4\0Class 5\0Class 6\0Class 7\0Class 8\0Class 9\0Class 10\0\0"));

			static int item_current_3 = 0;
			ImGui::Combo("                   ", &item_current_3, xorstr_("Primary\0Secondary\0\0"));
			if (ImGui::BeginCombo(xorstr_("##combo"), current_item)) // The second parameter is the label previewed before opening the combo.
			{
				for (int n = 0; n < IM_ARRAYSIZE(items); n++)
				{
					bool is_selected = (current_item == items[n]); // You can store your selection however you want, outside or inside your objects
					if (ImGui::Selectable(items[n], is_selected))
						current_item = items[n];
					if (is_selected)
						ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
				}
				ImGui::EndCombo();
			}
			
			ImGui::RadioButton(xorstr_("MP"), &gameMode, 0);

			ImGui::SameLine();

			ImGui::RadioButton(xorstr_("WZ"), &gameMode, 1);

			//ImGui::SameLine();
			if (ImGui::Button(xorstr_("  Set Camo  "), ImVec2(200, 30)))
			{

				//g_vars->goffsets.mwcamoAddr = utility::PointerChain(g_vars->hProc, g_vars->baseModule + g_vars->goffsets.camoAddr, { 0x1830, 0xBB033 });
				if (current_item == "(MW) Gold")
					SetCamo(item_current_2, item_current_3, 111);

				if (current_item == "(MW) Platinum")
					SetCamo(item_current_2, item_current_3, 112);

				if (current_item == "(MW) Damascus")
					SetCamo(item_current_2, item_current_3, 113);

				if (current_item == "(MW) Obsidian")
					SetCamo(item_current_2, item_current_3, 114);

				if (current_item == "(CW) Gold")
					SetCamo(item_current_2, item_current_3, 133);

				if (current_item == "(CW) Diamond")
					SetCamo(item_current_2, item_current_3, 134);

				if (current_item == "(CW) DMU")
					SetCamo(item_current_2, item_current_3, 135);

				if (current_item == "(CW) Golden Viper")
					SetCamo(item_current_2, item_current_3, 242);

				if (current_item == "(CW) Plague Diamond")
					SetCamo(item_current_2, item_current_3, 243);

				if (current_item == "(CW) Dark Aether")
					SetCamo(item_current_2, item_current_3, 244);

				if (current_item == "(VG) Gold")
					SetCamo(item_current_2, item_current_3, 345);

				if (current_item == "(VG) Diamond")
					SetCamo(item_current_2, item_current_3, 346);

				if (current_item == "(VG) Atomic")
					SetCamo(item_current_2, item_current_3, 350);

				if (current_item == "(VG) Fake Diamond")
					SetCamo(item_current_2, item_current_3, 349);

				if (current_item == "(VG) Golden Viper")
					SetCamo(item_current_2, item_current_3, 402);

				if (current_item == "(VG) Plague Diamond")
					SetCamo(item_current_2, item_current_3, 403);

				if (current_item == "(VG) Dark Aether")
					SetCamo(item_current_2, item_current_3, 404); 

				if (current_item == "(CW) Cherry Blossom")
					SetCamo(item_current_2, item_current_3, 160);

				if (current_item == "(MW) Acticamo")
					SetCamo(item_current_2, item_current_3, 2);

				if (current_item == "(MW) Banded")
					SetCamo(item_current_2, item_current_3, 3);
			}

			ImGui::Unindent(10);

			ImGui::Dummy(ImVec2(0.0f, 1.5f));
			static const char* itemclantag[] = { "Logo IW", "Logo RVN", "Logo SHG","Logo DW","Logo HMS","Logo BNOX","Logo 3ARC","Logo VV","Logo TFB","Red 1W","Red LW","Red IW DEV","Red RAVN","Red RAVEN","Red R4VEN", "Red OW", "Red BN0X","Red 34RC","Red ATVI", "Red MLG" };
			static const char* current_clantag = "Select Clan Tag";
			ImGuiPP::CenterText("Clan Tag Editor", 1, TRUE);
			ImGui::Indent(10);
			if (ImGui::BeginCombo("##combo4", current_clantag)) // The second parameter is the label previewed before opening the combo.
			{
				for (int n = 0; n < IM_ARRAYSIZE(itemclantag); n++)
				{
					bool is_selected4 = (current_clantag == itemclantag[n]); // You can store your selection however you want, outside or inside your objects
					if (ImGui::Selectable(itemclantag[n], is_selected4))
						current_clantag = itemclantag[n];
					if (is_selected4)
						ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
				}
				ImGui::EndCombo();
			}
		

			if (ImGui::Button(xorstr_("  Set Clan Tag  "), ImVec2(200, 30)))
			{
				if (current_clantag == "Logo IW")
					CL_PlayerData_SetCustomClanTag("iw");
				if (current_clantag == "Logo RVN")
					CL_PlayerData_SetCustomClanTag("rvn");
				if (current_clantag == "Logo SHG")
					CL_PlayerData_SetCustomClanTag("shg");
				if (current_clantag == "Logo DW")
					CL_PlayerData_SetCustomClanTag("dw");
				if (current_clantag == "Logo HMS")
					CL_PlayerData_SetCustomClanTag("hms");
				if (current_clantag == "Logo BNOX")
					CL_PlayerData_SetCustomClanTag("bnox");
				if (current_clantag == "Logo 3ARC")
					CL_PlayerData_SetCustomClanTag("3arc");
				if (current_clantag == "Logo VV")
					CL_PlayerData_SetCustomClanTag("vv");
				if (current_clantag == "Logo TFB")
					CL_PlayerData_SetCustomClanTag("tfb");
				if (current_clantag == "Red 1W")
					CL_PlayerData_SetCustomClanTag("1W");
				if (current_clantag == "Red LW")
					CL_PlayerData_SetCustomClanTag("LW");
				if (current_clantag == "Red IW DEV")
					CL_PlayerData_SetCustomClanTag("IWDev");
				if (current_clantag == "Red RAVN")
					CL_PlayerData_SetCustomClanTag("RAVN");
				if (current_clantag == "Red RAVEN")
					CL_PlayerData_SetCustomClanTag("RAVEN");
				if (current_clantag == "Red R4VEN")
					CL_PlayerData_SetCustomClanTag("R4VEN");
				if (current_clantag == "Red OW")
					CL_PlayerData_SetCustomClanTag("OW");
				if (current_clantag == "Red BN0X")
					CL_PlayerData_SetCustomClanTag("BN0X");
				if (current_clantag == "Red 34RC")
					CL_PlayerData_SetCustomClanTag("34RC");
				if (current_clantag == "Red ATVI")
					CL_PlayerData_SetCustomClanTag("ATVI");
				if (current_clantag == "Red MLG")
					CL_PlayerData_SetCustomClanTag("MLG");
			}


			ImGui::InputTextWithHint(xorstr_("##KeyInput"), xorstr_("Custom Clan Tag"), customtag, 5);

			if (ImGui::Button(xorstr_("  Set Custom Tag  "), ImVec2(200, 30)))
			{
				CL_PlayerData_SetCustomClanTag(customtag);
			}

			ImGui::PopItemWidth();
			ImGui::Unindent(10);
        } ImGui::EndChild();

    } ImGui::End();
}