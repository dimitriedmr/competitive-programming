import java.util.*;

public class Main {

	static class Solution {
		List<Integer> occurrencesList = new ArrayList<Integer>();

		private int transform(int n){
			int sum = 0;
			int digit = 0;
			while(n>0){
				digit = n%10;
				sum += digit * digit;
				n/=10;
			}
			return sum;
		}

		public boolean isHappy(int n) {
			boolean happy = false;
			if (n == 1)
				happy = true;
			else{
				if(occurrencesList.contains(n) == false){
					occurrencesList.add(n);
					happy = isHappy(transform(n));
				}
				else
					happy = false;
			}
			return happy;
		}
	}
    public static void main(String[] args) {
		try {

			Solution s = new Solution();
			int[] testArray = {7,2,1,19,4,6,789,190219};

			for(int testnbr : testArray)
				System.out.println(s.isHappy(testnbr));

		} catch (Exception e) {

			System.out.println("Something went wrong.");
			e.printStackTrace();

		}
    }
}
