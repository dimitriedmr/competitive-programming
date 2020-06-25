#include <stdio.h>

#define RELEASE 1
#define START_EXP_LEN 9
#define END_EXP_LEN 3

static const char startExp[10] = "a list of";
static const char endExp[4] = "and";
static const char errorAnswer[11] = "AMBIGUOUS";
static char answer[999];

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
    else if(inputChar == ',')
    {
      //answer[answerIndex++] = ' ';
    }else if(inputChar == ' ' || inputChar == '\n' || inputChar == '\r')
    {
      //do nothing
    }else if(inputChar >= 'A' && inputChar <= 'Z')
    {
      if(answer[answerIndex - 1] != '(')
        answer[answerIndex++] = ' ';
      noElements = false;
      
      if(endFlag == true)
      {
        while(inputChar >= 'A' && inputChar <= 'Z')
        {
          answer[answerIndex++] = inputChar;
          inputChar = getchar();
        }
        answer[answerIndex++] = ')';
        endFlag = false; //reset
      }
      else
      {
        while(inputChar >= 'A' && inputChar <= 'Z')
        {
          answer[answerIndex++] = inputChar;
          inputChar = getchar();
        }
        if(inputChar == ',')
        {
        }
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
      
      if(answerIndex > 0 && answer[answerIndex - 1] >= 'A' && answer[answerIndex - 1] <= 'Z')
        answer[answerIndex++] = ' ';
      answer[answerIndex++]='(';
      startFlag = false; //reset
    }
  } while (inputChar != '\n' && !errorFlag);
  
  if(openLists > closeLists)
  {
    if(openLists == 1 && answerIndex != 1)
    {
      for(int tempIndex = 0; tempIndex < answerIndex && !errorFlag; ++ tempIndex)
      {
        if(answer[tempIndex]== ' ')
          errorFlag = true;
      }
      answer[answerIndex++] = ')';
    }
    else
    {
      errorFlag = true;
    }
    if(closeLists)
    {
      errorFlag = true;
    }
  }
  //while(openLists > closeLists)
  //{
  //  answer[answerIndex++] = ')';
  //  closeLists++;
  //}
  answer[answerIndex]='\0';
  if(errorFlag)
  {
    puts(errorAnswer);
  }
  else
  {
    puts(answer);
  }
  
  //flush
  while (inputChar != '\n')
  {
    inputChar = getchar();
  } 

}

int main ()
{
  // problem statement:
  // http://codeforces.com/gym/100963
  // A
    
  unsigned long long N = 0; 
#ifndef RELEASE
  freopen ("gym_100963_A.in","r",stdin);
#endif
  scanf("%llu\n",&N);
  
  while(N > 0)
  { 
    processLine();
    N = N - 1;
  }
#ifndef RELEASE
  fclose(stdin);
#endif
  return 0;
}
