class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {
        vector<vector<pair<int, int>>> graph(n + 1);
        for (const auto& road : roads) {
            int u = road[0];
            int v = road[1];
            int dist = road[2];
            graph[u].push_back({v, dist});
            graph[v].push_back({u, dist});
        }
        
        int min_score = INT_MAX;
        vector<bool> visited(n + 1, false);
        queue<int> q;
        
        q.push(1);
        visited[1] = true;
        
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            
            for (const auto& neighbor : graph[curr]) {
                int next_node = neighbor.first;
                int weight = neighbor.second;
                
                min_score = min(min_score, weight);
                
                if (!visited[next_node]) {
                    visited[next_node] = true;
                    q.push(next_node);
                }
            }
        }
        
        return min_score;
    }
};