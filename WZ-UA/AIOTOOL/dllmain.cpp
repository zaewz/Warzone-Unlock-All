#include "dllmain.h"
#include <sys/stat.h>

HANDLE hMainThread = NULL;

float crosshair_col[3] = { 255.f / 255.f, 255.f , 255.f };
int screenX = GetSystemMetrics(SM_CXSCREEN);
int screenY = GetSystemMetrics(SM_CYSCREEN);

ImColor crosshaircolor = ImColor(0.f, 0.f, 255.f, 255.f);

bool is_key_down(int vk_key)
{
	return ((GetAsyncKeyState(vk_key) & 0x8000) ? 1 : 0);
}

//#ifndef  NDEBUG
void Log_(const char* fmt, ...) {
	char		text[4096];
	va_list		ap;
	va_start(ap, fmt);
	vsprintf_s(text, fmt, ap);
	va_end(ap);

	std::ofstream logfile(xorstr_("C:\\aiotool\\debug\\aio_debuglog.logs"), std::ios::app);
	if (logfile.is_open() && text)	logfile << text << std::endl;
	logfile.close();
}
//#endif
bool IsPathExist(const std::string& s)
{
	struct stat buffer;
	return (stat(s.c_str(), &buffer) == 0);
}


uint64_t BASEIMAGE = reinterpret_cast<uint64_t>(GetModuleHandleA(NULL));

void init()
{
	g_vars = new global_vars();
	g_vars->procID = utility::GetProcId(L"ModernWarfare.exe");
	g_vars->hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, g_vars->procID);
	g_vars->baseModule = (QWORD)(iat(GetModuleHandleA).get()("ModernWarfare.exe"));
	g_vars->hWind = process::get_process_window();

}

__declspec(dllexport)HRESULT present_hk(IDXGISwapChain3* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!pSwapChain)
		return ori_present(pSwapChain, SyncInterval, Flags);
	if (d3d12::pCommandQueue == nullptr)
	{
		ori_present(pSwapChain, SyncInterval, Flags);
	}

	DXGI_SWAP_CHAIN_DESC sdesc;
	pSwapChain->GetDesc(&sdesc);
	if (sdesc.OutputWindow == GetForegroundWindow())
	{
		Main = imgui::start(
			reinterpret_cast<IDXGISwapChain3*>(pSwapChain),
			reinterpret_cast<ID3D12CommandQueue*>((d3d12::pCommandQueue)), nullptr, 16.0f);

		imgui::imgui_frame_header();

		if (GetAsyncKeyState(VK_END) & 1)
			kiero::shutdown();

		if (GetAsyncKeyState(VK_HOME) & 1)
			g_vars->msettings.b_menuEnable = !g_vars->msettings.b_menuEnable;

		if (g_vars->msettings.b_menuEnable)
		{
			ImGui::GetIO().MouseDrawCursor;
			menu->MENUSHOW();
		}

		if (g_vars->msettings.chrosshair)
		{
			ImGui::Begin(xorstr_("##sussyLick"), nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse |
				ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar);
			DWORD ScreenCenterX = screenX / 2;
			DWORD ScreenCenterY = screenY / 2;
			ImGui::GetOverlayDrawList()->AddLine(ImVec2(ScreenCenterX - 12, ScreenCenterY), ImVec2((ScreenCenterX - 12) + (12 * 2), ScreenCenterY), crosshaircolor, 1.0);
			ImGui::GetOverlayDrawList()->AddLine(ImVec2(ScreenCenterX, ScreenCenterY - 12), ImVec2(ScreenCenterX, (ScreenCenterY - 12) + (12 * 2)), crosshaircolor, 1.0);
			ImGui::End();
		}

		if (g_vars->msettings.b_dynamic3p)
		{
			/*dvar_set2("NOSLRNTRKL", 1);*/
			if (is_key_down(VK_RBUTTON) || is_key_down(VK_GAMEPAD_LEFT_TRIGGER))
			{
				dvar_set2("NOSLRNTRKL", 0);
			}
			else
			{
				dvar_set2("NOSLRNTRKL", 1);
			}
		}
	
		imgui::imgui_no_border();
		g_game::init(Main);
		imgui::imgui_frame_end();
	}
	return ori_present(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI  initthread(HMODULE hModule)
{
	hMainThread = GetCurrentThread();

	init();

	if (g_vars->procID)
	{
	    g_vars->goffsets.unlock_offsets = utility::PatternScanEx(g_vars->hProc, g_vars->baseModule + 0x500000, 0x1F0000, xorstr_("\x33\xFF\x48\x8D\x15\x00\x00\x00\x00\x48\x89\x05\x00\x00\x00\x00\x48\x8D\x0D"), xorstr_("xxxxx????xxx????xxx")) - g_vars->baseModule;
		g_vars->goffsets.Dvar_FindVarByName = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x2000000, 0x1F00000, xorstr_("\x48\x83\xEC\x48\x49\x8B\xC8\xE8\x00\x00\x00\x00"), xorstr_("xxxxxxxx????"), 1, 5, 7);
		g_vars->goffsets.Dvar_SetBoolInternal = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x2000000, 0x1F00000, xorstr_("\xE8\x00\x00\x00\x00\x80\x3D\x00\x00\x00\x00\x00\x4C\x8D\x35\x00\x00\x00\x00\x74\x43\x33\xD2\xF7\x05\x00\x00\x00\x00\x00\x00\x00\x00\x76\x2E"), xorstr_("x????xx?????xxx????xxxxxx????????xx"), 1, 5, 0);
		g_vars->goffsets.Dvar_SetInt_Internal = utility::PatternScanEx(g_vars->hProc, g_vars->baseModule + 0x3000000, 0x1F00000, xorstr_("\x40\x53\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x84\x24\x00\x00\x00\x00\x0F\xB6\x41\x09\x48\x8B\xD9"), xorstr_("xxxxx????xxx????xxxxxxx????xxxxxxx")) - g_vars->baseModule;
		g_vars->goffsets.Dvar_SetBoolByName = utility::PatternScanEx(g_vars->hProc, g_vars->baseModule + 0x3000000, 0x1F00000, xorstr_("\x48\x89\x5C\x24\x00\x57\x48\x81\xEC\x00\x00\x00\x00\x0F\xB6\xDA"), xorstr_("xxxx?xxxx????xxx")) - g_vars->baseModule;
		g_vars->goffsets.Dvar_SetFloat_Internal = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x6000000, 0x1F00000, xorstr_("\xE8\x00\x00\x00\x00\x45\x0F\x2E\xC8"), xorstr_("x????xxxx"), 1, 5, 0);
		g_vars->goffsets.camoAddr = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x2000000, 0x1F00000, xorstr_("\x4C\x8B\x00\x00\x00\x00\x00\x4C\x8B\x00\x00\x00\x00\x00\x4D\x85\x00\x74\x00\x49\xB9"), xorstr_("xx?????xx?????xx?x?xx"),3,7,0);
		g_vars->goffsets.camoAddr += 0x28;
		g_vars->goffsets.ddl_loadasset = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x3300000, 0x1F00000, xorstr_("\xe8\x00\x00\x00\x00\x48\x8b\x00\x4c\x8d\x4c\x24\x00\x33\xc0\x48\x8d\x0d\x00\x00\x00\x00"), xorstr_("x????xx?xxxx?xxxxx????"), 1, 5, 0);
		g_vars->goffsets.ddl_getrootstate = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x2300000, 0x1F00000, xorstr_("\xe8\x00\x00\x00\x00\x8b\x0d\x00\x00\x00\x00\x0f\x10\x00"), xorstr_("x????xx????xx?"), 1, 5, 0);
		g_vars->goffsets.ddl_getdllbuffer = utility::PatternScanEx(g_vars->hProc, g_vars->baseModule + 0x4000000, 0x1F00000, xorstr_("\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x48\x89\x74\x24\x00\x57\x48\x83\xEC\x30\x48\x8B\xE9\x49\x63\xF8\x41\x8B\xC9\x48\x63\xF2\x41\x8B\xD9\xE8\x00\x00\x00\x00"), xorstr_("xxxx?xxxx?xxxx?xxxxxxxxxxxxxxxxxxxxx????")) - g_vars->baseModule;	;
		g_vars->goffsets.ddl_movetoname = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x4000000, 0x1F00000, xorstr_("\xE8\x00\x00\x00\x00\x84\xC0\x74\x22\x48\x8D\x54\x24\x40"), xorstr_("x????xxxxxxxxx"), 1, 5, 0);;
	    g_vars->goffsets.ddl_movetopath = utility::PatternScanEx(g_vars->hProc, g_vars->baseModule + 0x6500000, 0xF00000, "\x48\x89\x74\x24\x00\x48\x89\x7C\x24\x00\x41\x56\x48\x83\xEC\x20\x4D\x8B\xF1\x48\x8B\xFA\x48\x85\xC9", "xxxx?xxxx?xxxxxxxxxxxxxxx") - g_vars->baseModule;
		g_vars->goffsets.ddl_setint = utility::FindOffset(g_vars->hProc, g_vars->baseModule + 0x4000000, 0x1F00000, xorstr_("\x44\x8B\xC0\x48\x8D\x55\xB7\x48\x8D\x4C\x24\x00\xE8\x00\x00\x00\x00"), xorstr_("xxxxxxxxxxx?x????"), 1, 5, 12);
		g_vars->goffsets.ddl_setstring = utility::PatternScanEx(g_vars->hProc, g_vars->baseModule + 0x6800000, 0xF00000, "\x48\x89\x5C\x24\x00\x48\x89\x74\x24\x00\x57\x48\x83\xEC\x30\x49\x8B\xF0\x48\x8B\xFA\x48\x8B\xD9\x48\x85\xD2\x0F\x84\x00\x00\x00\x00\x48\x8B\x42\x10\x48\x85\xC0\x0F\x84\x00\x00\x00\x00", "xxxx?xxxx?xxxxxxxxxxxxxxxxxxx????xxxxxxxxx????") - g_vars->baseModule;
		g_vars->goffsets.ddl_getint = utility::PatternScanExCustom(g_vars->hProc, g_vars->baseModule + 0x6500000, 0xF00000, "\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x20\x48\x8B\xFA\x48\x8B\xD9\x48\x85\xD2\x74\x7F\x48\x8B\x42\x10\x48\x85\xC0\x74\x76", "xxxx?xxxxxxxxxxxxxxxxxxxxxxxxx", 2) - g_vars->baseModule;
		g_vars->goffsets.a_parse = utility::PatternScanEx(g_vars->hProc, g_vars->baseModule + 0x02D00000, 0xF00000, "\x40\x55\x56\x41\x54\x41\x56\x41\x57\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x44\x24\x00\x45\x33\xF6\x4D\x8B\xF9\x45\x89\x31", "xxxxxxxxxxxx????xxx????xxxxxxx?xxxxxxxxx") - g_vars->baseModule;
		g_vars->goffsets.clantag_offset = utility::PatternScanEx(g_vars->hProc, g_vars->baseModule + 0x03C00000, 0xF00000, "\x40\x53\x48\x83\xEC\x30\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x44\x24\x00\x4C\x8B\xCA\x41\xB8\x00\x00\x00\x00\x8B\x15\x00\x00\x00\x00\x8B\xD9", "xxxxxxxxx????xxxxxxx?xxxxx????xx????xx") - g_vars->baseModule;


		if (kiero::init(kiero::RenderType::D3D12) == kiero::Status::Success)
		{
			kiero::bind(54, (void**)&oExecuteCommandListsD3D12, imgui::hookExecuteCommandListsD3D12);
			kiero::bind(140, (void**)&ori_present, present_hk);
		
		}
	}
	else
	{
		return 0;
	}


	return 0;
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		initthread(module);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
	return TRUE;
}