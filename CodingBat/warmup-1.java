public class Main {
    public static boolean sleepIn(boolean weekday, boolean vacation)
    {
      boolean sleep = false;
      if (!weekday | vacation)
      {
        sleep = true;
      }
      return sleep;
    }
    
    public static void main(String[] args)
    {
        try {
          
            System.out.println(sleepIn(false, false));
            System.out.println(sleepIn(true, false));
            System.out.println(sleepIn(false, true));
            System.out.println(sleepIn(true, true));

        } catch (Exception e) {

            System.out.println("Something went wrong.");
            e.printStackTrace();

        }
    }
}
