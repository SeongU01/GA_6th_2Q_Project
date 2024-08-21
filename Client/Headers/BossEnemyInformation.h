#pragma once
namespace BossEnemy
{
	enum class FSM
	{
		None, Idle, Move, 
		LaserWave, RealLaserWave,
		MeteorSlash, RealMeteorSlash,
		LaserBurst,
		SonicStab,
		ReadyMove,
		SpawnRange,
		Death, End
	};
}
