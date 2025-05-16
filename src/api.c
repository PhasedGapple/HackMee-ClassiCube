#include "api.h"
#include "Commands.h"
#include "Chat.h"
#include "String.h"
#include "Event.h"
#include "Game.h"
#include "Logger.h"
#include "Server.h"
#include "World.h"
#include "Inventory.h"
#include "Entity.h"
#include "Window.h"
#include "Graphics.h"
#include "Funcs.h"
#include "Block.h"
#include "EnvRenderer.h"
#include "Utils.h"
#include "TexturePack.h"
#include "Options.h"
#include "Drawer2D.h"
#include "Protocol.h"
#include "Stream.h"
#include "Entity.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "Camera.h"
#include "Core.h"
#include <time.h>
#include "Menus.h"
#include "Gui.h"
#include "PackedCol.h"
#include "Widgets.h"
#include "Commands.h"
#include <fcntl.h>
#include <string.h>

Vec3 startPos1;
Vec3 endPos1;
Vec3 curPos;
BlockID block;
cc_bool xdone = true;
cc_bool ydone = true;
cc_bool zdone = true;
cc_bool taskActive = false;
cc_bool guivisible = false;
cc_string client = String_FromConst("HackMee");
int y;


//-----------------------------------


static void nop() {}


//-----------------------------------
void API_SortFill(Vec3 startPos, Vec3 endPos, BlockID block1)
{
	startPos1.x = startPos.x;
	startPos1.y = startPos.y;
	startPos1.z = startPos.z;

	endPos1.x = endPos.x;
	endPos1.y = endPos.y;
	endPos1.z = endPos.z;
	
	if (startPos1.x >= endPos.x)
	{
		startPos1.x = endPos.x;
		endPos1.x = startPos.x;
	}
	if (startPos1.y >= endPos.y)
	{
		startPos1.y = endPos.y;
		endPos1.y = startPos.y;
	}
	if (startPos1.z >= endPos.z)
	{
		startPos1.z = endPos.z;
		endPos1.z = startPos.z;
	}
	
	curPos.x = startPos1.x;
	curPos.y = startPos1.y;
	curPos.z = startPos1.z;
	block = block1;
	xdone = false;
	ydone = true;
	zdone = true;
	taskActive = true;
	y = startPos1.y;
}

void API_Fill()
{
	if (!taskActive) {
		return;  // Exit the function early if the task is no longer active
	}
	if (xdone == true) {}
	else
	{
		Game_ChangeBlock(curPos.x, curPos.y, curPos.z, block);
		if (curPos.x == endPos1.x) { xdone = true; ydone = false; curPos.x = startPos1.x; if (curPos.y == endPos1.y) {} else { y = y + 1; curPos.y = y; } }
		else { curPos.x = curPos.x + 1; }
		char playerPositionString[50]; // Adjust size as needed

		sprintf(playerPositionString, "/client tp %f %f %f",
			curPos.x,
			curPos.y,
			curPos.z);
		const cc_string w = String_FromRawArray(playerPositionString);
		Commands_Execute(&w);
		
	}
	if (ydone == true) {}
	else
	{
		if (curPos.x == endPos1.x + 1) {
			if (curPos.y == endPos1.y)
			{
				ydone = true; zdone = false;
			}
			else { y = y + 1; curPos.x = startPos1.x; curPos.y = y; }
		}
		else { Game_ChangeBlock(curPos.x, curPos.y, curPos.z, block); curPos.x = curPos.x + 1; }
		char playerPositionString[50]; // Adjust size as needed
		
		sprintf(playerPositionString, "/client tp %f %f %f",
			curPos.x,
			curPos.y,
			curPos.z);
		const cc_string w = String_FromRawArray(playerPositionString);
		Commands_Execute(&w);
	}
	if (zdone == true) {}
	else
	{
		if (curPos.z == endPos1.z) {
			zdone = true;
			taskActive = false;
		}
		else { curPos.z = curPos.z + 1; curPos.x = startPos1.x; y = startPos1.y; curPos.y = y; xdone = false; zdone = true; }
	}
}

//---------------------------------------------
void API_SortFillBot(Vec3 startPos, Vec3 endPos, BlockID block1)
{
	cc_string args = String_FromRawArray("Alland20201 38f058f8fc29340b3282fdbb045692ba 72.83.224.234 25565");
	Process_StartGame2(&args, 3);
	startPos1.x = startPos.x;
	startPos1.y = startPos.y;
	startPos1.z = startPos.z;

	endPos1.x = endPos.x;
	endPos1.y = endPos.y;
	endPos1.z = endPos.z;

	if (startPos1.x >= endPos.x)
	{
		startPos1.x = endPos.x;
		endPos1.x = startPos.x;
	}
	if (startPos1.y >= endPos.y)
	{
		startPos1.y = endPos.y;
		endPos1.y = startPos.y;
	}
	if (startPos1.z >= endPos.z)
	{
		startPos1.z = endPos.z;
		endPos1.z = startPos.z;
	}

	curPos.x = startPos1.x;
	curPos.y = startPos1.y;
	curPos.z = startPos1.z;
	block = block1;
	xdone = false;
	ydone = true;
	zdone = true;
	taskActive = true;
	y = startPos1.y;
}

void API_FillBot()
{
	if (!taskActive) {
		return;  // Exit the function early if the task is no longer active
	}
	if (xdone == true) {}
	else
	{
		char playerPositionString[50]; // Adjust size as needed

		sprintf(playerPositionString, "/client tp %f %f %f",
			curPos.x,
			curPos.y,
			curPos.z);
		const cc_string w = String_FromRawArray(playerPositionString);
		Commands_Execute(&w);
		Game_ChangeBlock(curPos.x, curPos.y, curPos.z, block);
		if (curPos.x == endPos1.x) { xdone = true; ydone = false; curPos.x = startPos1.x; if (curPos.y == endPos1.y) {} else { y = y + 1; curPos.y = y; } }
		else { curPos.x = curPos.x + 1; }

	}
	if (ydone == true) {}
	else
	{
		char playerPositionString[50]; // Adjust size as needed

		sprintf(playerPositionString, "/client tp %f %f %f",
			curPos.x,
			curPos.y,
			curPos.z);
		const cc_string w = String_FromRawArray(playerPositionString);
		Commands_Execute(&w);
		if (curPos.x == endPos1.x + 1) {
			if (curPos.y == endPos1.y)
			{
				ydone = true; zdone = false;
			}
			else { y = y + 1; curPos.x = startPos1.x; curPos.y = y; }
		}
		else { Game_ChangeBlock(curPos.x, curPos.y, curPos.z, block); curPos.x = curPos.x + 1; }
	}
	if (zdone == true) {}
	else
	{
		if (curPos.z == endPos1.z) {
			zdone = true;
			taskActive = false;
		}
		else { curPos.z = curPos.z + 1; curPos.x = startPos1.x; y = startPos1.y; curPos.y = y; xdone = false; zdone = true; }
	}
}

//---------------------------------------------

#define PAUSE_MAX_BTNS 6
static struct PauseScreen {
	Screen_Body
		int descsCount;
	const struct SimpleButtonDesc* descs;
	struct ButtonWidget btns[PAUSE_MAX_BTNS], quit;
	struct TextWidget title;
} PauseScreen;

static void PauseScreen1Base_Quit(void* a, void* b) {
	Window_RequestClose();
}

static void PauseScreen1Base_Game(void* a, void* b) {
	Gui_Remove((struct Screen*)&PauseScreen);
}

static void PauseScreen1Base_ContextRecreated(struct PauseScreen* s, struct FontDesc* titleFont) {
	Screen_UpdateVb(s);
	Gui_MakeTitleFont(titleFont);
	Menu_SetButtons(s->btns, titleFont, s->descs, s->descsCount);
	TextWidget_SetConst(&s->title, "&4Hack&bMee &fMenu", titleFont);
}

static void PauseScreen1Base_AddWidgets(struct PauseScreen* s, int width) {
	static const struct SimpleButtonDesc descs1[] = { -150,   50, "Not set.",          nop };
	TextWidget_Add(s, &s->title);
	Menu_AddButtons(s, s->btns, width, s->descs, s->descsCount);
}

static struct Widget* pause_widgets[1 + 6 + 2];

static void PauseScreen1_CheckHacksAllowed(void* screen) {
	struct PauseScreen* s = (struct PauseScreen*)screen;
	if (Gui.ClassicMenu) return;
	// Widget_SetDisabled(&s->btns[1],
	// 	!Entities.CurPlayer->Hacks.CanAnyHacks); /* select texture pack */
	s->dirty = true;
}

static void PauseScreen1_ContextRecreated(void* screen) {
	struct PauseScreen* s = (struct PauseScreen*)screen;
	struct FontDesc titleFont;
	PauseScreen1Base_ContextRecreated(s, &titleFont);

	ButtonWidget_SetConst(&s->quit, "Quit game", &titleFont);
	PauseScreen1_CheckHacksAllowed(s);
	Font_Free(&titleFont);
}

static void PauseScreen1_Layout(void* screen) {
	struct PauseScreen* s = (struct PauseScreen*)screen;
	Menu_LayoutButtons(s->btns, s->descs, s->descsCount);
	Widget_SetLocation(&s->quit, ANCHOR_MAX, ANCHOR_MAX, 5, 5);
	Widget_SetLocation(&s->title, ANCHOR_CENTRE, ANCHOR_CENTRE, 0, -200);
}

static void Btn_ClickOption1() { cc_string args = (String_FromRawArray("")); CuboidCommand_Execute(&args, 1); }
static void Btn_ClickOption2() {
	cc_string args = (String_FromRawArray("motd"));
	bypassCMD_Execute(&args, 1);
}
static void Btn_ClickClose(void* w, int x, int y) {}

static void PauseScreen1_Init(void* screen) {
	struct PauseScreen* s = (struct PauseScreen*)screen;
	static const struct SimpleButtonDesc descs[] = {
		{ -325,  -200, "&bPosFly",        PosFlyCMD_Executer },
		{ -325,  -150, "&0Car Mode",      carCMD_Executer  },
		{ -325,  -100, "&4Hacks Bypass",  Btn_ClickOption2	 },
		{ -325,  -50,  "&bNuker",         NukerCMD_Execute  },
		{ -325,    0,  "&dCuboid",        Btn_ClickOption1 },
		{  225,  215,  "Close GUI",       API_PauseScreen1_Show }
	};

	s->widgets = pause_widgets;
	s->numWidgets = 0;
	s->maxWidgets = Array_Elems(pause_widgets);
	s->widgetsPerPage = 3;
	Event_Register_(&UserEvents.HackPermsChanged, s, PauseScreen1_CheckHacksAllowed);

	s->descs = descs;
	s->descsCount = Array_Elems(descs);
	PauseScreen1Base_AddWidgets(s, 150);
	ButtonWidget_Add(s, &s->quit, 120, PauseScreen1Base_Quit);
	s->maxVertices = Screen_CalcDefaultMaxVertices(s);


}

static void PauseScreen1_Free(void* screen) {
	Event_Unregister_(&UserEvents.HackPermsChanged, screen, PauseScreen1_CheckHacksAllowed);
}

static const struct ScreenVTABLE PauseScreen_VTABLE = {
	PauseScreen1_Init,   nop, PauseScreen1_Free,
	MenuScreen_Render2, Screen_BuildMesh,
	Menu_InputDown,     Screen_InputUp,    nop, nop,
	Menu_PointerDown,   Screen_PointerUp,  Menu_PointerMove, nop,
	PauseScreen1_Layout, Screen_ContextLost, PauseScreen1_ContextRecreated,
	nop
};
void API_PauseScreen1_Show() {
	struct PauseScreen* s = &PauseScreen;
	s->grabsInput = true;
	s->closable = false;
	s->VTABLE = &PauseScreen_VTABLE;
	if (guivisible == false)
	{
		Gui_Add((struct Screen*)s, GUI_PRIORITY_MENU);
		guivisible = true;
	}
	else
	{
		Gui_Remove(Gui_GetScreen(GUI_PRIORITY_MENU));
		guivisible = false;
	}
}
