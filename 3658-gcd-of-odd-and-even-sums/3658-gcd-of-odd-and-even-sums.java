class Solution {
    public int gcdOfOddEvenSums(int n) {
        
        int sumOdd = 0;
        int sumEven = 0;

        for (int i = 1; i<= n; i++) {
            sumOdd += (2 * i -1);
            sumEven += (2 * i);
        }
        for (int d = Math.min(sumOdd, sumEven); d >= 1; d-- ){
            if (sumOdd % d == 0 && sumEven % d ==0){
                return d;
            }
        }

        return 1;
    }
}