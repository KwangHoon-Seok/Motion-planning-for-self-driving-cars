#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Node {
    int x, y;
    int g, h; // g(n): 시작점에서 현재 노드까지의 비용, h(n): 휴리스틱 비용
    Node* parent;

    Node(int x, int y, int g = 0, int h = 0, Node* parent = nullptr)
        : x(x), y(y), g(g), h(h), parent(parent) {}

    int f() const { return g + h; } // f(n) = g(n) + h(n)

    bool operator>(const Node& other) const { return f() > other.f(); }
};

// 휴리스틱 함수: 맨해튼 거리
int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

vector<Node> get_neighbors(const Node& node, int rows, int cols) {
    vector<Node> neighbors;
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    for (auto& d : directions) {
        int nx = node.x + d.first;
        int ny = node.y + d.second;

        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
            neighbors.emplace_back(nx, ny);
        }
    }
    return neighbors;
}

vector<pair<int, int>> reconstruct_path(Node* node) {
    vector<pair<int, int>> path;
    while (node != nullptr) {
        path.emplace_back(node->x, node->y);
        node = node->parent;
    }
    reverse(path.begin(), path.end());
    return path;
}

vector<pair<int, int>> a_star(int startX, int startY, int goalX, int goalY, int rows, int cols) {
    priority_queue<Node, vector<Node>, greater<Node>> openSet;
    unordered_map<int, unordered_map<int, int>> g_score; // g(n) 값을 저장하기 위한 맵
    Node start(startX, startY, 0, heuristic(startX, startY, goalX, goalY));
    openSet.push(start);
    g_score[startX][startY] = 0;

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        if (current.x == goalX && current.y == goalY) {
            return reconstruct_path(&current);
        }

        for (Node neighbor : get_neighbors(current, rows, cols)) {
            int tentative_g_score = current.g + 1; // 가중치가 1인 경우

            if (!g_score.count(neighbor.x) || !g_score[neighbor.x].count(neighbor.y) || tentative_g_score < g_score[neighbor.x][neighbor.y]) {
                g_score[neighbor.x][neighbor.y] = tentative_g_score;
                int h = heuristic(neighbor.x, neighbor.y, goalX, goalY);
                neighbor.g = tentative_g_score;
                neighbor.h = h;
                neighbor.parent = new Node(current); // 부모 노드를 저장하여 경로 추적 가능
                openSet.push(neighbor);
            }
        }
    }

    return {}; // 경로를 찾을 수 없는 경우 빈 벡터 반환
}

int main() {
    int rows = 5, cols = 5;
    int startX = 0, startY = 0;
    int goalX = 4, goalY = 4;

    vector<pair<int, int>> path = a_star(startX, startY, goalX, goalY, rows, cols);

    if (!path.empty()) {
        cout << "Path found:\n";
        for (auto& p : path) {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << endl;
    } else {
        cout << "No path found." << endl;
    }

    return 0;
}
