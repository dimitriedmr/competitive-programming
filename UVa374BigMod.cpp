#include <stdio.h>
#include <iostream>

using namespace std;

template <class T>
class Solution
{
  private:
    T B, P, M;
    T binExp (T base, T power, T modulo);   
  public: 
    Solution():B(0),P(0),M(0){};
    void readParameters();
    T solve ();
};

template <class T>
T Solution<T>::solve ()
{
  T R = this->binExp(this->B,this->P,this->M);
  return R;
}

template <class T>
void Solution<T>::readParameters ()
{
  cin >> this->B >> this->P >> this->M;
}

template <class T>
T Solution<T>::binExp (T base, T power, T modulo)
{
  T answer = 1;
  T newFactor = base % modulo;
  while(power > 0)
  {
    if(power & 1)
    {
      answer = answer * newFactor % modulo;
    }
    power = power >> 1;
    newFactor = newFactor * newFactor % modulo;
  }
  return answer;
}

int main ()
{
  // problem statement:
  // http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=310
  
  Solution<unsigned long long> s;
  s.readParameters();
  while (!cin.eof())
  { 
    cout << s.solve() << endl;
    s.readParameters();
  }
    
  return 0;
}
