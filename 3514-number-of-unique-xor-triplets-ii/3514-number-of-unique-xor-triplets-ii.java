class Solution {
    public int uniqueXorTriplets(int[] nums) {
        int maxVal = 0;
        for (int num : nums) {
            maxVal = Math.max(maxVal, num);
        }
        int T = 1 << (32 - Integer.numberOfLeadingZeros(maxVal));
        T = Math.max(T, 8); 
        
        boolean[] s1 = new boolean[T];
        boolean[] s2 = new boolean[T];
        
        for (int i = 0; i < nums.length; i++) {
            for (int j = i; j < nums.length; j++) {
                s1[nums[i] ^ nums[j]] = true;
            }
        }
        
        for (int i = 0; i < T; i++) {
            if (s1[i]) {
                for (int num : nums) {
                    s2[i ^ num] = true;
                }
            }
        }
        
        int count = 0;
        for (int i = 0; i < T; i++) {
            if (s2[i]) {
                count++;
            }
        }
        return count;
    }
}
