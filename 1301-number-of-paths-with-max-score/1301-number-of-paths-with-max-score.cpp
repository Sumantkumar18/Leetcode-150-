#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        int MOD = 1e9 + 7;
        
        vector<vector<pair<int, int>>> dp(n, vector<pair<int, int>>(n, {0, 0}));
        dp[n - 1][n - 1] = {0, 1};
        
        int dirs[3][2] = {{1, 0}, {0, 1}, {1, 1}};
        
        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                if ((i == n - 1 && j == n - 1) || board[i][j] == 'X') {
                    continue;
                }
                
                int max_score = -1;
                int paths_count = 0;
                
                for (auto& dir : dirs) {
                    int ni = i + dir[0];
                    int nj = j + dir[1];
                    
                    if (ni < n && nj < n && dp[ni][nj].second > 0) {
                        if (dp[ni][nj].first > max_score) {
                            max_score = dp[ni][nj].first;
                            paths_count = dp[ni][nj].second;
                        } else if (dp[ni][nj].first == max_score) {
                            paths_count = (paths_count + dp[ni][nj].second) % MOD;
                        }
                    }
                }
                
                if (max_score != -1) {
                    int current_val = (board[i][j] == 'E') ? 0 : (board[i][j] - '0');
                    dp[i][j] = {max_score + current_val, paths_count};
                }
            }
        }
        
        if (dp[0][0].second == 0) {
            return {0, 0};
        }
        
        return {dp[0][0].first, dp[0][0].second};
    }
};