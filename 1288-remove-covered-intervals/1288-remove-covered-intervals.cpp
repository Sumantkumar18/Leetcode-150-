class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& a_next) {
            if (a[0] == a_next[0]) {
                return a[1] > a_next[1];
            }
            return a[0] < a_next[0];
        });

        int remaining = 0;
        int current_end = 0;

        for (const auto& interval : intervals) {
            if (interval[1] > current_end) {
                remaining++;
                current_end = interval[1];
            }
        }

        return remaining;
    }
};