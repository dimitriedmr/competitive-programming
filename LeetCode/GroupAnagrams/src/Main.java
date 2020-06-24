import java.lang.reflect.Array;
import java.util.List;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Arrays;

public class Main {

    static class Solution {
        HashMap<String, List<String>> anagrams = new HashMap<String, List<String>>();

        private void addValueForKey(String key, String value) {
            List<String> values = anagrams.get(key);
            if (values == null) {
                values = new ArrayList<String>();
            }
            values.add(value);
            anagrams.put(key, values);
        }

        public List<List<String>> groupAnagrams(String[] strs) {
            List<List<String>> output = new ArrayList<List<String>>();

            for (String word : strs) {
                char[] wordRearranged = word.toCharArray();
                Arrays.sort(wordRearranged);
                addValueForKey(String.valueOf(wordRearranged), word);
            }

            System.out.println(anagrams);

            for (List<String> words : anagrams.values()) {
                output.add(words);
            }

            return output;
        }
    }

    public static void main(String[] args) {
        try {

            Solution s = new Solution();
            String[] testArray = {"eat", "tea", "tan", "ate", "nat", "bat"};
            System.out.println(s.groupAnagrams(testArray));
            s = new Solution();
            String[] testArray2 = {"cab", "tin", "pew", "duh", "may", "ill", "buy", "bar", "max", "doc"};
            System.out.println(s.groupAnagrams(testArray2));
            s = new Solution();
            String[] testArray3 = {"cab", "pug", "pei", "nay", "ron", "rae", "ems", "ida", "mes"};
            System.out.println(s.groupAnagrams(testArray3));

        } catch (Exception e) {

            System.out.println("Something went wrong.");
            e.printStackTrace();

        }
    }
}
