#pragma once

enum class LayerGroup { Tile, Object, Player, Enemy, UI, End };
enum class RenderGroup { BackGround, Tile, BackEffect, Object, FrontEffect, UI, Card, Fade, End };
enum class SoundGroup { BGM, SFX, Voice, End };

enum class CardType { Attack, Move, Support };
enum class CardEffectType { None };

static const int WINCX = 1920;
static const int WINCY = 1080;

static const TCHAR* rootPath = L"../Resources/";