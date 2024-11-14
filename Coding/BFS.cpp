#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 그래프를 인접 리스트로 표현
class Graph {
    int V; // 정점의 개수
    vector<vector<int>> adj; // 인접 리스트

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    // 간선을 추가하는 함수
    void addEdge(int v, int w) {
        adj[v].push_back(w); // 정점 v에서 정점 w로 가는 간선 추가
        adj[w].push_back(v); // 무방향 그래프로 설정 (양방향 간선)
    }

    // BFS 알고리즘 함수
    void BFS(int start) {
        vector<bool> visited(V, false); // 방문 여부를 저장하는 벡터
        queue<int> q; // BFS 탐색에 사용할 큐

        // 시작 정점을 방문하고 큐에 삽입
        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " "; // 방문한 정점 출력

            // 현재 정점에 연결된 모든 정점을 탐색
            for (int i : adj[v]) {
                if (!visited[i]) { // 아직 방문하지 않은 정점인 경우
                    visited[i] = true; // 방문 표시
                    q.push(i); // 큐에 추가
                }
            }
        }
    }
};

int main() {
    Graph g(8); // 정점의 개수가 8인 그래프 생성

    // 간선 추가
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(3, 6);
    g.addEdge(4, 5);
    g.addEdge(5, 6);
    g.addEdge(6, 7);
    g.addEdge(4, 7);

    cout << "BFS starting from node 0: ";
    g.BFS(0); // 정점 0에서 BFS 탐색 시작

    return 0;
}
