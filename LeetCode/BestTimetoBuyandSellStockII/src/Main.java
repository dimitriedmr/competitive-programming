public class Main {

    static class Solution {
        public int maxProfit(int[] prices) {
            int profit = 0;
            int buy = prices[0], sell = 0;
            int n = prices.length;
            for (int index = 1; index < n; ++index) {
                if (prices[index - 1] > prices[index]) {
                    if (sell != 0) {
                        profit += sell - buy;
                        sell = 0;
                    }
                    buy = prices[index];
                }else {
                    sell = prices[index];
                }
            }
            if(sell != 0){
                profit += sell - buy;
            }
            return profit;
        }
    }

    public static void main(String[] args) {
        try {

            Solution s = new Solution();
            int[] testArray = {7, 1, 5, 3, 6, 4};
            int[] testArray2 = {1, 2, 3, 4, 5};
            int[] testArray3 = {7, 6, 4, 3, 1};

            System.out.println(s.maxProfit(testArray));
            System.out.println(s.maxProfit(testArray2));
            System.out.println(s.maxProfit(testArray3));

        } catch (Exception e) {

            System.out.println("Something went wrong.");
            e.printStackTrace();

        }
    }
}
