class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();

        vector<vector<int>> dis(n, vector<int>(n, 1e9));
        queue<pair<int,int>> q;

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j]) {
                    dis[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        while(!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            for(int k = 0; k < 4; k++) {
                int nx = x + dx[k];
                int ny = y + dy[k];

                if(nx >= 0 && ny >= 0 && nx < n && ny < n &&
                   dis[nx][ny] > dis[x][y] + 1) {
                    dis[nx][ny] = dis[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }

        auto check = [&](int val) {
            if(dis[0][0] < val || dis[n-1][n-1] < val) return false;

            queue<pair<int,int>> qq;
            vector<vector<int>> vis(n, vector<int>(n, 0));

            qq.push({0,0});
            vis[0][0] = 1;

            while(!qq.empty()) {
                auto [x, y] = qq.front();
                qq.pop();

                if(x == n-1 && y == n-1) return true;

                for(int k = 0; k < 4; k++) {
                    int nx = x + dx[k];
                    int ny = y + dy[k];

                    if(nx >= 0 && ny >= 0 && nx < n && ny < n &&
                       !vis[nx][ny] && dis[nx][ny] >= val) {
                        vis[nx][ny] = 1;
                        qq.push({nx, ny});
                    }
                }
            }

            return false;
        };

        int l = 0, r = 2 * n;

        while(l < r) {
            int mid = (l + r + 1) / 2;
            if(check(mid)) l = mid;
            else r = mid - 1;
        }

        return l;
    }
};