public class Main {

	static class Solution {
		public int maxSubArray(int[] nums) {
			int maxSum = Integer.MIN_VALUE;
			int sum = 0;
			for (int nbr : nums){
				sum  += nbr;
				if (maxSum < sum)
					maxSum = sum;
				if(sum < 0)
					sum = 0;
			}
			return maxSum;
		}
	}
    public static void main(String[] args) {
		try {

			Solution s = new Solution();
			int[] testArray = {-2,1,-3,4,-1,2,1,-5,4};

			System.out.println(s.maxSubArray(testArray));

		} catch (Exception e) {

			System.out.println("Something went wrong.");
			e.printStackTrace();

		}
    }
}
