#include <queue>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <vector>

#include "Tile.h"
#include "Client_Define.h"

struct Vector3Hash {
    std::size_t operator()(const Vector3& v) const {
        return std::hash<int>()((int)v.x) ^ std::hash<int>()((int)v.y) ^ std::hash<int>()((int)v.z);
    }
};

struct Node {
    Vector3 position;
    float gCost, hCost;
    std::shared_ptr<Node> pParent;

    Node(const Vector3& pos)
        : position(pos), gCost(0), hCost(0), pParent(nullptr) {}
    Node() : position{ 0, 0, 0 }, gCost(0), hCost(0), pParent(nullptr) {}

    float fCost() const {
        return gCost + hCost;
    }

    bool operator==(const Node& other) const {
        return ((int)position.x == (int)other.position.x && (int)position.y == (int)other.position.y);
    }
};

struct NodeCompare {
    bool operator()(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b) const {
        return a->fCost() > b->fCost();
    }
};

float heuristic(const Vector3& a, const Vector3& b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

std::vector<Vector3> getNeighbors(const Vector3& pos, const std::vector<std::vector<Tile*>>& grid, Vector3 goal) {
    std::vector<Vector3> neighbors;
    std::vector<Vector3> directions = { {1, 0, 0}, {0, 1, 0}, {-1, 0, 0}, {0, -1, 0} };

    for (const auto& dir : directions) {
        Vector3 neighborPos = { pos.x + dir.x, pos.y + dir.y, pos.z };
        if (neighborPos.x >= 0 && (int)neighborPos.x < (int)grid[0].size() &&
            neighborPos.y >= 0 && (int)neighborPos.y < (int)grid.size() &&
            (grid[(int)neighborPos.y][(int)neighborPos.x]->canMove || ((int)goal.x==(int)neighborPos.x ) && ((int)goal.y == (int)neighborPos.y))) {
            neighbors.push_back(neighborPos);
        }
    }
    return neighbors;
}

std::vector<Vector3> reconstructPath(const std::shared_ptr<Node>& currentNode) {
    std::vector<Vector3> path;
    std::shared_ptr<Node> node = currentNode;
    while (node != nullptr) {
        path.push_back(node->position);
        node = node->pParent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<Vector3> AStar(const Vector3& start, const Vector3& goal, const std::vector<std::vector<Tile*>>& grid) {
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, NodeCompare> openSet;
    std::unordered_map<Vector3, std::shared_ptr<Node>, Vector3Hash> allNodes;

    auto startNode = std::make_shared<Node>(start);
    auto goalNode = std::make_shared<Node>(goal);
    openSet.push(startNode);
    allNodes[start] = startNode;

    while (!openSet.empty()) {
        auto currentNode = openSet.top();
        openSet.pop();

        if (*currentNode == *goalNode) {

            return reconstructPath(currentNode->pParent);
        }

        for (const auto& neighborPos : getNeighbors(currentNode->position, grid,goal)) {
            float tentativeGCost = currentNode->gCost + 1;
            std::shared_ptr<Node> neighborNode;

            if (allNodes.find(neighborPos) == allNodes.end()) {
                neighborNode = std::make_shared<Node>(neighborPos);
                neighborNode->pParent = currentNode;
                allNodes[neighborPos] = neighborNode;
            }
            else {
                neighborNode = allNodes[neighborPos];
                if (tentativeGCost >= neighborNode->gCost) continue;
            }

            neighborNode->gCost = tentativeGCost;
            neighborNode->hCost = heuristic(neighborPos, goal);
            neighborNode->pParent = currentNode;
            openSet.push(neighborNode);
        }
    }
    return std::vector<Vector3>(); // 경로를 찾지 못함
}

//동적할당뺴기..