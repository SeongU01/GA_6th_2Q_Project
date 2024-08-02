#pragma once

enum class LayerGroup { Tile, Object, Player, Enemy, UI, End };
enum class RenderGroup { BackGround, Tile, Object, Player, FrontObject, FrontEffect, Plat, UI, Fade, End };
enum class SoundGroup { BGM, SFX, Voice, End };

static const int WINCX = 1920;
static const int WINCY = 1080;

static const TCHAR* rootPath = L"../Resources/";