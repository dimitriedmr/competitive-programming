#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

struct poz
{
  int l, c;
} sol[100];

int d[100], dl[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1};
int a[11][11];
int n, m, is, js, k;

void init (int k)
{
  d[k] = - 1;
}

int exista(int k)
{
  if(d[k] < 3) return 1;
  else return 0;
}


void valpos(int k)
{
  sol[k].l = sol[k - 1].l + dl[d[k]];

  sol[k].c = sol[k - 1].c + dc[d[k]];
}

int cont(int k)
{
  int i;
  if(a[sol[k].l][sol[k].c] == 1) return 0;

  if(sol[k].l < 1 || sol[k].l > n || sol[k].c < 1 || sol[k].c > m)
    return 0;

  for(i = 1; i <= k - 1; i++)
    if(sol[i].l == sol[k].l && sol[i].c == sol[k].c)
      return 0;
  
  return 1;
}


int solutie (int k)
{
  if(sol[k].l == 1 || sol[k].l  == n || sol[k].c == 1 || sol[k].c == m)
    return 1;
  else return 0;
}

void tipar(int k)
{
  int i;
  for(i = 1; i <= k; i++)
    cout << sol[i].l << ' ' << sol[i].c << ' ';
  cout << endl;
}

void bktr()
{
  k = 2; init(k);
  while(k > 1)
  {
    if(exista(k))
    {
      d[k] = d[k] + 1;
      valpos(k);
      if(cont(k))
        if(solutie(k))
          tipar(k);
        else
        {
          k++;
          init(k);
        }
    }
    else k--;
  }
}

int main()
{
  int c = 0;
  cin >> n >> m;
  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= m; j++)
      cin >> a[i][j];
  cin >> is >> js;
  sol[1].l = is;
  sol[1].c = js;
  bktr();
  return 0;   

}