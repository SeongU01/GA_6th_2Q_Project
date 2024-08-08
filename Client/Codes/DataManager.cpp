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
	// �� ���� ������
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
	// �� ���� ������
	std::getline(file, line);
	std::getline(file, line);
	std::wstringstream wss(line);
	int stageCount = 0;
	wss >> stageCount;
	_objectInfo.resize(stageCount);
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
		objInfo.objectPositionInfo.resize(objectCount);

		for (size_t j = 0; j < objectCount; j++)
		{
			std::getline(file, line);
			std::wstringstream wssLine(line);
			std::getline(wssLine, token, L',');
			std::pair<int, Vector3>tempPair;
			tempPair.first = _wtoi(token.c_str());
			std::getline(wssLine, token, L',');
			tempPair.second.x = (float)_wtof(token.c_str());
			std::getline(wssLine, token, L',');
			tempPair.second.y = (float)_wtof(token.c_str());
			objInfo.objectPositionInfo[j]=tempPair;
		}

		_objectInfo[i] = objInfo;
	}

	file.close();
	return true;
}

void DataManager::Free()
{
}
