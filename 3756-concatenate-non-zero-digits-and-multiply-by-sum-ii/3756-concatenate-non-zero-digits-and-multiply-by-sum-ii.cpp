#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    const int MOD = 1e9 + 7;

    long long power(long long base, long long exp) {
        long long res = 1;
        base %= MOD;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % MOD;
            base = (base * base) % MOD;
            exp /= 2;
        }
        return res;
    }

    long long modInverse(long long n) {
        return power(n, MOD - 2);
    }

public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int m = s.length();
        long long inv10 = modInverse(10);

        vector<long long> pow10(m + 1, 1);
        vector<long long> powInv10(m + 1, 1);
        for (int i = 1; i <= m; i++) {
            pow10[i] = (pow10[i - 1] * 10) % MOD;
            powInv10[i] = (powInv10[i - 1] * inv10) % MOD;
        }

        vector<long long> pref_x(m + 1, 0);
        vector<long long> pref_sum(m + 1, 0);
        vector<int> pref_c(m + 1, 0);

        for (int i = 0; i < m; i++) {
            int digit = s[i] - '0';
            pref_c[i + 1] = pref_c[i] + (digit != 0);
            pref_sum[i + 1] = pref_sum[i] + digit;

            if (digit != 0) {
                long long term = (digit * powInv10[pref_c[i + 1]]) % MOD;
                pref_x[i + 1] = (pref_x[i] + term) % MOD;
            } else {
                pref_x[i + 1] = pref_x[i];
            }
        }

        vector<int> answer;
        answer.reserve(queries.size());

        for (const auto& q : queries) {
            int l = q[0], r = q[1];

            long long current_sum = pref_sum[r + 1] - pref_sum[l];

            long long x_part = (pref_x[r + 1] - pref_x[l] + MOD) % MOD;
            long long x = (x_part * pow10[pref_c[r + 1]]) % MOD;

            long long ans = (x * current_sum) % MOD;
            answer.push_back(ans);
        }

        return answer;
    }
};