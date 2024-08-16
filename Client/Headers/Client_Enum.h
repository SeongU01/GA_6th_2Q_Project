#pragma once

enum class LayerGroup { Tile, Player, Object, Enemy, UI, End };
enum class RenderGroup { None, BackGround, Tile, BackEffect, Object, FrontEffect, UI, Card, ToolTip, Top, Fade, End };
enum class SoundGroup { BGM, SFX, Voice,Battle,Card, End };

// Card
enum class CardType { Attack, Move, Support };
enum class CardEffectType { None, RangeAttack, RangeCast, PathMove, SelfCast, Reload, Draw, PathAttack };
enum class CardAttribute { None, OverClock };

enum AttributeFlag : unsigned long long
{
	Shield		= 1 << 1,
	Extra		= 1 << 2,
	Charge		= 1 << 3,
	HighPower	= 1 << 4,
	OverCharge	= 1 << 5,
	WeakPoint	= 1 << 6
};

static const int WINCX = 1920;
static const int WINCY = 1080;

static const TCHAR* rootPath = L"../Resources/";