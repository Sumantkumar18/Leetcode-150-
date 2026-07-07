class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration, vector<int>& waterStartTime, vector<int>& waterDuration) {
        int n = landStartTime.size();
        int m = waterStartTime.size();
        int min_finish_time = INT_MAX;
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int land_finish = landStartTime[i] + landDuration[i];
                int total_finish_A = max(land_finish, waterStartTime[j]) + waterDuration[j];
                
                int water_finish = waterStartTime[j] + waterDuration[j];
                int total_finish_B = max(water_finish, landStartTime[i]) + landDuration[i];
                
                min_finish_time = min({min_finish_time, total_finish_A, total_finish_B});
            }
        }
        
        return min_finish_time;
    }
};