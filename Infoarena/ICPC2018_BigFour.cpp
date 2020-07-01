#include <fstream>
	
#include <iostream>
	
using namespace std;
	
 
	
ifstream in("bigfour.in");
	
ofstream out("bigfour.out");
	
 
	
#define MAX 4
	
int D, v[MAX], b[MAX];
	
bool stop = false;
	
 
	
void init(int k)
	
{
	
	b[k] = -1;
	
}
	
 
	
bool succesor(int k)
	
{
	
	if (b[k] < MAX - 1) {
	
		b[k]++;
	
		return true;
	
	}
	
	return false;
	
}
	
 
	
bool valid(int k)
	
{
	
	for (int i = 0; i < k; i++)
	
		if (b[k] == b[i])
	
			return false;
	
	return true;
	
}
	
 
	
bool solutie(int k)
	
{
	
	return (k == MAX - 1);
	
}
	
 
	
bool solve()
	
{
	
	int s = v[b[0]];
	
	for (int i = 1; i < MAX; i++)
	
	{
	
		int t = v[b[i]];
	
		if (abs(s - t) <= D)
	
		{
	
			s += t;
	
		}
	
		else
	
		{
	
			return false;
	
		}
	
	}
	
	return true;
	
}
	
 
	
bool solve2() 
	
{
	
	if (abs(v[b[0]] - v[b[1]]) <= D && abs(v[b[2]] - v[b[3]]) <= D)
	
	{
	
		int s1 = v[b[0]] + v[b[1]];
	
		int s2 = v[b[2]] + v[b[3]];
	
		if (abs(s1 - s2) <= D) {
	
			return true;
	
		}
	
	}
	
	return false;
	
}
	
 
	
void back(int k) 
	
{
	
	init(k);
	
	while (succesor(k) && !stop)
	
		if (valid(k)) {
	
			if (solutie(k)) {
	
				if (solve() || solve2()) {
	
					out << "DA\n";
	
					stop = true;
	
				}
	
			}
	
			else {
	
				back(k + 1);
	
			}
	
		}
	
			
	
}
	
 
	
int main()
	
{
	
	int T;
	
	in >> T;
	
	while (T--) {
	
		in >> D;
	
		for (int i = 0; i < MAX; i++)
	
		{
	
			in >> v[i];
	
		}
	
		stop = false;
	
		back(0);
	
		if (stop == false)
	
			out << "NU\n";
	
	}
	
}
