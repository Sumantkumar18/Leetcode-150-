class Solution {
    public int removeDuplicates(int[] nums) {
        if (nums.length <= 2) {
            return nums.length;
        }
        
        int i = 2; 
        
        for (int n = 2; n < nums.length; n++) {
            if (nums[n] != nums[i - 2]) {
                nums[i] = nums[n];
                i++;
            }
        }
        
        return i;
    }
}