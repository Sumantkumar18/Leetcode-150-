import java.util.Arrays;

public class Solution {
    public int[] pathExistenceQueries(int n, int[] nums, int maxDiff, int[][] queries) {
        int MAX_VAL = 100000;
        boolean[] present = new boolean[MAX_VAL + 1];
        for (int num : nums) {
            present[num] = true;
        }

        int[] lastPresent = new int[MAX_VAL + 1];
        int last = -1;
        for (int i = 0; i <= MAX_VAL; i++) {
            if (present[i]) {
                last = i;
            }
            lastPresent[i] = last;
        }

        int LOG = 18;
        int[][] up = new int[LOG][MAX_VAL + 1];

        for (int x = 0; x <= MAX_VAL; x++) {
            if (!present[x]) {
                up[0][x] = x;
                continue;
            }
            int nextPos = Math.min(MAX_VAL, x + maxDiff);
            up[0][x] = lastPresent[nextPos];
        }

        for (int k = 1; k < LOG; k++) {
            for (int x = 0; x <= MAX_VAL; x++) {
                up[k][x] = up[k - 1][up[k - 1][x]];
            }
        }

        int[] answer = new int[queries.length];
        for (int i = 0; i < queries.length; i++) {
            int u = queries[i][0];
            int v = queries[i][1];

            if (u == v) {
                answer[i] = 0;
                continue;
            }

            int a = nums[u];
            int b = nums[v];

            if (a == b) {
                answer[i] = 1;
                continue;
            }

            if (a > b) {
                int temp = a;
                a = b;
                b = temp;
            }

            int steps = 0;
            for (int k = LOG - 1; k >= 0; k--) {
                if (up[k][a] < b && up[k][a] > a) {
                    a = up[k][a];
                    steps += (1 << k);
                }
            }

            if (a + maxDiff >= b && up[0][a] >= b) {
                answer[i] = steps + 1;
            } else {
                answer[i] = -1;
            }
        }

        return answer;
    }
}