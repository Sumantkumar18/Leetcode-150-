class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();

        vector<vector<pair<int,int>>> adj(n);
        vector<int> indegree(n, 0);

        int maxCost = 0;

        for (auto &e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
            indegree[e[1]]++;
            maxCost = max(maxCost, e[2]);
        }

        vector<int> topo;
        queue<int> q;

        for (int i = 0; i < n; i++)
            if (indegree[i] == 0)
                q.push(i);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topo.push_back(u);

            for (auto &p : adj[u]) {
                indegree[p.first]--;
                if (indegree[p.first] == 0)
                    q.push(p.first);
            }
        }

        auto check = [&](int limit) {
            long long INF = 1e18;
            vector<long long> dist(n, INF);
            dist[0] = 0;

            for (int u : topo) {
                if (dist[u] == INF)
                    continue;

                if (u != 0 && u != n - 1 && !online[u])
                    continue;

                for (auto &p : adj[u]) {
                    int v = p.first;
                    int w = p.second;

                    if (w < limit)
                        continue;

                    if (v != 0 && v != n - 1 && !online[v])
                        continue;

                    dist[v] = min(dist[v], dist[u] + w);
                }
            }

            return dist[n - 1] <= k;
        };

        int low = 0, high = maxCost, ans = -1;

        while (low <= high) {
            int mid = (low + high) / 2;

            if (check(mid)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return ans;
    }
};