#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// 무한 거리 정의
const int INF = numeric_limits<int>::max();

vector<int> dijkstra(int start, const vector<vector<pair<int, int>>> &graph){
    int n = graph.size();
    // node(graph)가 vector의 원소로 주어짐
    vector<int> dist(n, INF);
    vector<bool> visited(n, false);
    dist[start] = 0;

    for(int i = 0; i < n -1; ++i){
        int minDist = INF, currentNode = -1;
        for(int j = 0; j < n; ++j){
            if(!visited[j] && dist[j] < minDist){
                minDist = dist[j];
                currentNode = j;
            }
        }
        if (currentNode == -1) break;
        visited[currentNode] = true;

        for (const auto &neighbor : graph[currentNode]){
            int nextNode = neighbor.first;
            int weight = neighbor.second;
            if(dist[currentNode] + weight < dist[nextNode]){
                dist[nextNode] = dist[currentNode] + weight;
            }
        }
    }
    return dist;
}

int main() {
    int n, m, start;
    cout << "Enter the number of nodes and edges: ";
    cin >> n >> m;
    cout << "Enter the start node: ";
    cin >> start;

    vector<vector<pair<int, int>>> graph(n);
    cout << "Enter the edges (node1 node2 weight):\n";
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w); // 무방향 그래프인 경우 양쪽으로 추가
    }

    vector<int> distances = dijkstra(start, graph);

    cout << "Shortest distances from node " << start << ":\n";
    for (int i = 0; i < distances.size(); ++i) {
        if (distances[i] == INF)
            cout << "Node " << i << ": Unreachable\n";
        else
            cout << "Node " << i << ": " << distances[i] << "\n";
    }

    return 0;
}