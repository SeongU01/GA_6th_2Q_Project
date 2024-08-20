#pragma once
namespace BossEnemy
{
	enum class FSM
	{
		None, Idle, Move, 
		LaserWave, RealLAserWave,
		MeteorSlash, RealMeteorSlash,
		LaserBurst,
		SonicStab,
		ReadyMove,
		SpawnRange,
		Death, End
	};
}
