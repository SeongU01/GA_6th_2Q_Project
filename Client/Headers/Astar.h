#pragma once
#include "MonoBehavior.h"

struct Vector3Hash
{
	std::size_t operator()(const Vector3& v) const {
		return std::hash<int>()((int)v.x) ^ std::hash<int>()((int)v.y) ^ std::hash<int>()((int)v.z);
	}
};

struct Node
{
	Vector3 position;
	float gCost, hCost,fCost=0;
	std::shared_ptr<Node> pParent;

	Node(const Vector3& pos)
		: position(pos), gCost(0), hCost(0), pParent(nullptr) {}
	Node() : position{ 0, 0, 0 }, gCost(0), hCost(0), pParent(nullptr) {}

	float calculateFCost() const{
		return gCost + hCost;
	}

	bool operator==(const Node& other) const {
		return ((int)position.x == (int)other.position.x && (int)position.y == (int)other.position.y);
	}
};

struct NodeCompare
{
	bool operator()(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b) const {
		return a->calculateFCost() > b->calculateFCost();
	}
};

class GridMovement;
class Tile;
class AStar :public Engine::MonoBehavior
{
public:
	explicit AStar(const wchar_t* name,const std::wstring& targetName);
private:
	virtual ~AStar() = default;
public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
public:
	void SetGoalPosition(const Vector3& goalPos) { _goalPosition = goalPos; }
	void SetGridPosition(const Vector3& gridPos) { _gridPosition = gridPos; }
	void SetGridMovement(GridMovement* _move) { _movement = _move; }
	void SetMaxMoveSteps(int steps);
	bool CheckMoveEnd() { return !_isMoving; }
private:
	float heuristic(const Vector3& a, const Vector3& b);
	std::vector<Vector3> getNeighbors(const Vector3& pos, const std::vector<std::vector<Tile*>>& grid, Vector3 goal);
	std::vector<Vector3> reconstructPath(const std::shared_ptr<Node>& currentNode);
	std::vector<Vector3> AStarMove(const Vector3& start, const Vector3& goal, const std::vector<std::vector<Tile*>>& grid);

	//동적할당뺴기..
public:
	GridMovement* _movement = nullptr;
	Vector3 _gridPosition = { 0.f,2.f,0.f };
private:
	Engine::GameObject* _pTargetObject = nullptr;
	Vector3 _goalPosition;
	std::vector<Vector3> _path;
	std::wstring _targetObjectName;
	size_t _pathIndex = 0;
	float _moveTime = 0.7f;
	float _curTime = 0.f;
private:
	int _maxMoveSteps = 0;
	int _currentMoveSteps = 0;
	bool _isMoving = false;
};




