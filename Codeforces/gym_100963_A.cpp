#include <stdio.h>
#include <algorithm>

static const char startExp[10] = "a list of";
static const char endExp[4] = "and";
static const char errorAnswer[11] = "AMBIGUOUS";
static char answer[999];
#define START_EXP_LEN 9
#define END_EXP_LEN 3

static void prettyPrint(int length)
{
  int index = 0, index2 = 0, c = 0;
  for(index = 0; index < length; ++index)
  {
    c = answer[index];
    if(c != ')' && c != '(')
    {
      index2 = index - 1;
      if(index2 >= 0 && answer[index2] == ')')
      {
        printf(" ");
      }
      
      printf("%c", c);
      
      index2 = index + 1;
      if(index2 < length && answer[index2] != ')')
      {
        printf(" ");
      }
    }
    else
    {
      printf("%c",c);
    }
  }
}
static void checkEnds(bool &startFlag, bool &endFlag, bool &errorFlag)
{
  int startExpIndex = 1;
  int endExpIndex = 1;
  char inputChar = getchar();
  while(startExp[startExpIndex] == inputChar)
  {
    ++startExpIndex;
    inputChar = getchar();
  }  
  if(startExpIndex == START_EXP_LEN)
  {
    startFlag = true;
  }
  else
  {
    while(endExp[endExpIndex] == inputChar)
    {
      ++endExpIndex;
      inputChar = getchar();
    }  
    if(endExpIndex == END_EXP_LEN)
    {
      endFlag = true;
    }
    else
    {
      errorFlag = true;
    }
  }
}

void processLine()
{
  int inputChar = 0, answerIndex = 0;
  bool startFlag = false, endFlag = false, errorFlag = false;
  bool noElements = false;
  int openLists = 0, closeLists = 0;
  
  do {
    inputChar = getchar();
    if(inputChar == 'a')
    {
      checkEnds(startFlag,endFlag,errorFlag);
      
      if(startFlag)
      {
        if(!noElements)
        {
          ++openLists;
          noElements = true;
        }
        else
        {
          errorFlag = true;
        }
      }
      else if(endFlag)
      {
        ++closeLists;
        if(closeLists > openLists)
        {
          errorFlag = true;
        }
      }
    }
    else if(inputChar == ',' || inputChar == ' ' || 
            inputChar == '\n' || inputChar == '\r')
    {
      //do nothing
    }else if(inputChar >= 'A' && inputChar <= 'Z')
    {
      answer[answerIndex++] = inputChar;
      
      noElements = false;
      
      if(endFlag == true)
      {
        answer[answerIndex++] = ')';
        endFlag = false; //reset
      }
    }else
    {
      
      if(answerIndex)
      {
        errorFlag = true;
      }
    }
    
    if(startFlag == true)
    {
      answer[answerIndex++]='(';
      startFlag = false; //reset
    }
  } while (inputChar != '\n' && !errorFlag);
  
  while(openLists > closeLists)
  {
    answer[answerIndex++] = ')';
    closeLists++;
  }
  
  answer[answerIndex]='\0';
  
  if(errorFlag)
  {
    do
    {
      inputChar = getchar(); //flush
    } while (inputChar != '\n');
    printf(errorAnswer);
  }
  else
  {
    prettyPrint(answerIndex);
  }

}

int main ()
{
  // problem statement:
  // http://codeforces.com/gym/100963
  // A
    
  unsigned long long N = 0; 
  
  //freopen ("gym_100963_A.in","r",stdin);
  scanf("%llu\n",&N);
  
  while(N > 0)
  { 
    processLine();
    printf ("\n");
    N = N - 1;
  }
  //fclose(stdin);
  return 0;
}
