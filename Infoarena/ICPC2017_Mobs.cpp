#include <iostream>
	
#include <fstream>
	
#include <cmath>
	
#include <algorithm>
	
using namespace std;
	
 
	
ifstream in("mobs.in");
	
ofstream out("mobs.out");
	
 
	
int main()
	
{
	
    int t;
	
    unsigned long long N;
	
    unsigned long long A, B;
	
    unsigned long long mici, medii;
	
    in >> t;
	
    while (t--) {
	
        in >> N >> A >> B;
	
        unsigned long long *health = new unsigned long long[N];
	
        unsigned long long x;
	
        unsigned long long timp = 0;
	
        unsigned long long timp_medii = 0;
	
 
	
        mici = 0;
	
        medii = 0;
	
        unsigned long long max_dmg, min_dmg;
	
        if (A<B)
	
        {
	
            min_dmg = A;
	
            max_dmg = B;
	
        }
	
        else
	
        {
	
            min_dmg = B;
	
            max_dmg = A;
	
        }
	
        while (N--) {
	
            in >> x;
	
            if (x > max_dmg) {
	
                timp++;
	
            }
	
            else if (x <= min_dmg) {
	
                mici++;
	
            }
	
            else {
	
                health[medii++] = x;
	
            }
	
        }
	
        if (mici >= medii) {
	
            timp += medii + ceil((mici - medii)/2.);
	
        }
	
        else {
	
            timp += mici;
	
            sort(health, health+medii);
	
            medii -=mici;
	
            unsigned long long dmg_monstru_mediu_curent = 0;
	
            unsigned long long i = 0;
	
            for ( i = 0; i<medii && timp_medii + dmg_monstru_mediu_curent <= medii - i; i++) {
	
                timp_medii += dmg_monstru_mediu_curent;
	
                dmg_monstru_mediu_curent = ceil((double)health[i]/min_dmg);
	
            }
	
            timp += medii - i;
	
        }
	
        out << timp << endl;
	
    }
	
    return 0;
	
}
