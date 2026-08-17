class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();
        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) prefix[i+1] = prefix[i] + stoneValue[i];

        vector<vector<int>> dp(n, vector<int>(n, 0));
        vector<vector<int>> PLeft(n, vector<int>(n, 0));
        vector<vector<int>> PRight(n, vector<int>(n, 0));

        auto sum = [&](int a, int b) -> long long {
            return prefix[b + 1] - prefix[a];
        };

        for (int len = 1; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                if (len > 1) {
                    // smallest k in [i, j-1] with leftSum(k) >= rightSum(k)
                    int lo = i, hi = j - 1, k = j; // k == j => no such k in range
                    while (lo <= hi) {
                        int mid = lo + (hi - lo) / 2;
                        long long L = sum(i, mid), R = sum(mid + 1, j);
                        if (L >= R) { k = mid; hi = mid - 1; }
                        else lo = mid + 1;
                    }

                    int best = 0;
                    // strictly-left region: p < k, guaranteed leftSum < rightSum
                    if (k - 1 >= i) best = max(best, PLeft[i][k - 1]);
                    // boundary point k itself (if it exists in range)
                    if (k <= j - 1) {
                        long long L = sum(i, k), R = sum(k + 1, j);
                        if (L == R) best = max(best, PLeft[i][k]); // tie: left option also valid
                        best = max(best, PRight[j][k + 1]);        // right option (covers k..j-1)
                    }
                    dp[i][j] = best;
                }
                int val = dp[i][j] + (int)sum(i, j);
                PLeft[i][j]  = (j > i) ? max(PLeft[i][j-1], val)  : val;
                PRight[j][i] = (j > i) ? max(PRight[j][i+1], val) : val;
            }
        }

        return dp[0][n - 1];
    }
};