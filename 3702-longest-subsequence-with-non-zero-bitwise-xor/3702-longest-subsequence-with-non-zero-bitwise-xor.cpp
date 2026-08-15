class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int totalXor = 0;
        bool hasNonZero = false;
        for (int num : nums) {
            totalXor ^= num;
            if (num != 0) hasNonZero = true;
        }
        
        if (totalXor != 0) return nums.size();
        if (hasNonZero) return nums.size() - 1;
        return 0;
    }
};