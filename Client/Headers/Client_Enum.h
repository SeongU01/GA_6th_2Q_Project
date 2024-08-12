#pragma once

enum class LayerGroup { Tile, Player, Object, Enemy, UI, End };
enum class RenderGroup {None, BackGround, Tile, BackEffect, Object, FrontEffect, UI, Card, Fade, End };
enum class SoundGroup { BGM, SFX, Voice, End };

// Card
enum class CardType { Attack, Move, Support };
enum class CardEffectType { RangeAttack, RangeCast, PathMove, SelfCast, Reload, Draw };
enum AdditiveFlag : unsigned long long
{
	Shield		= 1 << 0,
	Extra		= 1 << 1,
	Charge		= 1 << 2,
	HighPower	= 1 << 3,
	OverCharge	= 1 << 4,
	WeakPoint	= 1 << 5
};

static const int WINCX = 1920;
static const int WINCY = 1080;

static const TCHAR* rootPath = L"../Resources/";