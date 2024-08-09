#include "DataManager.h"

bool DataManager::LoadMap(const wchar_t* filePath)
{
	std::wstring path = filePath;
	std::wifstream file((path + L"/Map.csv").c_str());
	if (!file.is_open())
	{
		throw std::runtime_error("Can not open file");
		return false;
	}

	std::wstring line;
	// 맨 윗줄 버리기
	std::getline(file, line);
	std::getline(file, line);
	std::wstringstream wss(line);
	int mapCount = 0;
	wss >> mapCount;
	_mapInfos.resize(mapCount);
	for (size_t i = 0; i < mapCount; i++)
	{
		MapInfo mapInfo;
		std::getline(file, line);
		std::wstring token;
		std::wstringstream wss(line);
		std::getline(wss, token, L',');
		mapInfo.stageName = token;

		std::getline(file, line);
		std::wstringstream wssSize(line);
		std::getline(wssSize, token, L',');
		mapInfo.width = (float)_wtof(token.c_str());
		std::getline(wssSize, token, L',');
		mapInfo.height = (float)_wtof(token.c_str());

		std::getline(file, line);
		std::wstringstream wssOffset(line);
		std::getline(wssOffset, token, L',');
		mapInfo.mapOffsetY = (float)_wtof(token.c_str());
		std::getline(wssOffset, token, L',');
		mapInfo.tileOffsetX = (float)_wtof(token.c_str());
		std::getline(wssOffset, token, L',');
		mapInfo.tileOffsetY = (float)_wtof(token.c_str());


		mapInfo.mapData.resize((size_t)mapInfo.height);

		for (size_t j = 0; j < mapInfo.height; j++)
		{
			mapInfo.mapData[j].resize((size_t)mapInfo.width);
			std::getline(file, line);
			std::wstringstream wssLine(line);
			for (size_t k = 0; k < mapInfo.width; k++)
			{
				std::getline(wssLine, token, L',');
				mapInfo.mapData[j][k] = _wtoi(token.c_str());
			}
		}

		_mapInfos[i] = mapInfo;
	}

	file.close();
	return true;
}

bool DataManager::LoadObjectArrange(const wchar_t* filePath)
{
	std::wstring path = filePath;
	std::wifstream file((path + L"/ObjectArrange.csv").c_str());
	if (!file.is_open())
	{
		throw std::runtime_error("Can not open file");
		return false;
	}

	std::wstring line;
	// 맨 윗줄 버리기
	std::getline(file, line);
	std::getline(file, line);
	std::wstringstream wss(line);
	int stageCount = 0;
	wss >> stageCount;
	_objectArrangeInfos.resize(stageCount);
	for (size_t i = 0; i < stageCount; i++)
	{
		ObjectArrangeInfo objInfo;
		std::getline(file, line);
		std::wstring token;
		std::wstringstream wss(line);
		std::getline(wss, token, L',');
		objInfo.stageName = token;
		std::getline(wss, token, L',');
		int objectCount = _wtoi(token.c_str());
		objInfo.objectInfos.resize(objectCount);
		
		for (size_t j = 0; j < objectCount; j++)
		{
			std::getline(file, line);
			std::wstringstream wssLine(line);
			std::getline(wssLine, token, L',');
			ObjectInfo temoObj;
			temoObj.objectID = _wtoi(token.c_str());
			std::getline(wssLine, token, L',');
			temoObj.objectPosition.x = (float)_wtof(token.c_str());
			std::getline(wssLine, token, L',');
			temoObj.objectPosition.y = (float)_wtof(token.c_str());
			std::getline(wssLine, token, L',');
			temoObj.objectTag = token;
			objInfo.objectInfos[j]= temoObj;
		}

		_objectArrangeInfos[i] = objInfo;
	}

	file.close();
	return true;
}

bool DataManager::LoadEnemySpawn(const wchar_t* filePath)
{
	std::wstring path = filePath;
	std::wifstream file((path + L"/Wave.csv").c_str());
	if (!file.is_open())
	{
		return false;
	}

	std::wstring line;
	std::getline(file, line); // 헤더 줄 건너뜀

	std::map<std::wstring, EnemySpawnInfo> enemySpawnMap;

	while (std::getline(file, line))
	{
		std::wistringstream sstream(line);
		std::wstring stageID, waveName, enemyType, enemyTarget;
		float spawnX, spawnY, subSpawnX, subSpawnY;

		// CSV 줄 파싱
		std::getline(sstream, stageID, L',');
		std::getline(sstream, waveName, L',');
		sstream >> spawnX;
		sstream.ignore(1); // 콤마 무시
		sstream >> spawnY;
		sstream.ignore(1); // 콤마 무시
		sstream >> subSpawnX;
		sstream.ignore(1); // 콤마 무시
		sstream >> subSpawnY;
		sstream.ignore(1); // 콤마 무시
		std::getline(sstream, enemyType, L',');
		std::getline(sstream, enemyTarget, L',');

		// 적 정보 생성
		EnemyInfo enemyInfo;
		enemyInfo.spawnPosition = { spawnX, spawnY, 0.f };
		enemyInfo.subSpawnPosition = { subSpawnX, subSpawnY, 0.f };
		enemyInfo.targetName = enemyTarget;

		// WaveInfo 찾거나 생성
		WaveInfo* waveInfo = nullptr;
		auto it = enemySpawnMap.find(stageID);
		if (it != enemySpawnMap.end())
		{
			// 스테이지가 존재하면, 해당 웨이브를 검색
			auto& waveInfos = it->second.waveInfos;
			for (auto& wave : waveInfos)
			{
				if (wave.waveName == waveName)
				{
					waveInfo = &wave;
					break;
				}
			}

			// 웨이브를 찾지 못하면, 새로 생성
			if (!waveInfo)
			{
				waveInfos.push_back(WaveInfo{ waveName, {} });
				waveInfo = &waveInfos.back();
			}
		}
		else
		{
			// 스테이지가 존재하지 않으면, 스테이지와 웨이브를 생성
			EnemySpawnInfo newSpawnInfo;
			newSpawnInfo.stageName = stageID;
			newSpawnInfo.waveInfos.push_back(WaveInfo{ waveName, {} });
			waveInfo = &newSpawnInfo.waveInfos.back();
			enemySpawnMap[stageID] = std::move(newSpawnInfo);
		}

		// 웨이브에 적 정보 추가
		waveInfo->enemyInfos.push_back(enemyInfo);
	}

	// 파싱된 데이터를 클래스 멤버 변수로 이동
	_enemySpawnInfos.reserve(enemySpawnMap.size());
	for (auto& [stageName, spawnInfo] : enemySpawnMap)
	{
		_enemySpawnInfos.push_back(std::move(spawnInfo));
	}

	return true;
}

bool DataManager::LoadToolTip(const wchar_t* filePath)
{
	std::wstring path = filePath;
	std::wifstream file((path + L"/ToolTip.csv").c_str());
	if (!file.is_open())
	{
		throw std::runtime_error("Can not open file");
		return false;
	}

	std::wstring line;
	// 맨 윗줄 버리기
	std::getline(file, line);
	std::getline(file, line);
	std::wstringstream wss(line);
	int TipCount = 0;
	wss >> TipCount;
	_ToolTipInfos.resize(TipCount);
	for (size_t i = 0; i < TipCount; i++)
	{
		ToolTipInfo objInfo;
		std::getline(file, line);
		std::wstring token;
		std::wstringstream wss(line);
		std::getline(wss, token, L',');
		objInfo._id = token.c_str();
		std::getline(wss, token, L',');
		objInfo._title = token.c_str();
		std::getline(wss, token, L',');
		objInfo._content = token.c_str();
		std::getline(wss, token, L',');
		objInfo._leftTop = token.c_str();


		_ToolTipInfos[i] = objInfo;
	}
	file.close();
	return true;
}

void DataManager::Free()
{
}
