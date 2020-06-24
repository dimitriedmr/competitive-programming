public class Main {

	static class Solution {
		public void moveZeroes(int[] nums) {
			int n = nums.length;
			int nxtPos = 0;
			//reposition nonzero numbers
			for (int nbr : nums){
				if(nbr != 0){
					nums[nxtPos] = nbr;
					++nxtPos;
				}
			}
			//change rest of array with zeros
			while(nxtPos < n){
				nums[nxtPos++]= 0;
			}
		}
	}
    public static void main(String[] args) {
		try {

			Solution s = new Solution();
			int[] testArray = {0,1,0,3,12};
			s.moveZeroes(testArray);
			for(int num : testArray)
				System.out.println(num);

		} catch (Exception e) {

			System.out.println("Something went wrong.");
			e.printStackTrace();

		}
    }
}
