#include <queue>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <vector>

#include "Tile.h"
#include "Client_Define.h"

struct Vector3Hash {
    std::size_t operator()(const Vector3& v) const {
        return std::hash<int>()(v.x) ^ std::hash<int>()(v.y) ^ std::hash<int>()(v.z);
    }
};

struct Node {
    Vector3 position;
    float gCost, hCost;
    Node* parent;

    Node(Vector3 pos, Node* parent = nullptr)
        : position(pos), gCost(0), hCost(0), parent(parent) {}

    float fCost() const {
        return gCost + hCost;
    }

    bool operator==(const Node& other) const {
        return ((int)position.x == (int)other.position.x && (int)position.y == (int)other.position.y);
    }
};

struct NodeCompare {
    bool operator()(const Node* a, const Node* b) const {
        return a->fCost() > b->fCost();
    }
};

float heuristic(const Vector3& a, const Vector3& b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

std::vector<Vector3> getNeighbors(const Vector3& pos, const std::vector<std::vector<Tile*>>& grid) {
    std::vector<Vector3> neighbors;
    std::vector<Vector3> directions = { {1, 0, 0}, {0, 1, 0}, {-1, 0, 0}, {0, -1, 0} };

    for (const auto& dir : directions) {
        Vector3 neighborPos = { pos.x + dir.x, pos.y + dir.y, pos.z };
        if (neighborPos.x >= 0 && neighborPos.x < grid[0].size() &&
            neighborPos.y >= 0 && neighborPos.y < grid.size() &&
            grid[neighborPos.y][neighborPos.x]->canMove) {
            neighbors.push_back(neighborPos);
        }
    }
    return neighbors;
}

std::vector<Vector3> reconstructPath(Node* currentNode) {
    std::vector<Vector3> path;
    while (currentNode != nullptr) {
        path.push_back(currentNode->position);
        currentNode = currentNode->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<Vector3> aStar(const Vector3& start, const Vector3& goal, const std::vector<std::vector<Tile*>>& grid) {
    std::priority_queue<Node*, std::vector<Node*>, NodeCompare> openSet;// 우선순위 큐로 열린 목록을 관리
    std::unordered_map<Vector3, Node*, Vector3Hash> allNodes; // 모든 노드를 관리할 맵

    Node* startNode = new Node(start);
    Node* goalNode = new Node(goal);
    openSet.push(startNode);
    allNodes[start] = startNode;

    while (!openSet.empty()) {
        Node* currentNode = openSet.top();
        openSet.pop();

        if (*currentNode == *goalNode) { //도착하면 끝.
            std::vector<Vector3> path = reconstructPath(currentNode); //경로재구성
            
            for (auto& pair : allNodes) { // 할당 해제
                delete pair.second;
            }
            delete goalNode; 
            return path;
        }

        for (const auto& neighborPos : getNeighbors(currentNode->position, grid)) { //현재 위치의 이동가능 이웃 탐색.
            float tentativeGCost = currentNode->gCost + 1; //이웃 위치까지의 비용은 현재위치에서 1을 더한값
            Node* neighborNode;
            if (allNodes.find(neighborPos) == allNodes.end()) { //없던 친구면 새로 만들어서 넣기.
                neighborNode = new Node(neighborPos, currentNode); 
                allNodes[neighborPos] = neighborNode;
            }
            else {//있던 친구면
                neighborNode = allNodes[neighborPos]; //있던거 넣기 
                if (tentativeGCost >= neighborNode->gCost) continue; //비용이 더 작은 것 선택
            }
            neighborNode->gCost = tentativeGCost; //비용넣기
            neighborNode->hCost = heuristic(neighborPos, goal);//휴리스틱 비용
            neighborNode->parent = currentNode; //이동 전 노드 체크.
            openSet.push(neighborNode); //만든 노드 넣어두기
        }
    }

    //이럴일없어야돼..
    for (auto& pair : allNodes) {
        delete pair.second;
    }
    delete goalNode;  // goalNode를 해제합니다.
    return std::vector<Vector3>(); // 경로를 찾지 못함
}

//동적할당뺴기..