public class Main {

	static class Solution{

		public int singleNumber(int[] nums) {

			int number = 0;
			for(int item : nums)
			{
				number ^= item;
			}
			return number;
		}

	}
    public static void main(String[] args) {
		try {

			Solution s = new Solution();
			int[] testArray = {2,2,1};
			int[] testArray2 = {4,1,2,1,2};

			System.out.println(s.singleNumber(testArray));
			System.out.println(s.singleNumber(testArray2));

		} catch (Exception e) {

			System.out.println("Something went wrong.");
			e.printStackTrace();

		}
    }
}
