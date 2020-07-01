#include <fstream>
	
#include <cstring>
	
 
	
using namespace std;
	
 
	
ifstream in("entropy.in");
	
ofstream out("entropy.out");
	
 
	
#define MOVE_1_to_2 'm'
	
#define MOVE_1_to_3 'n'
	
#define MOVE_2_to_1 'o'
	
#define MOVE_2_to_3 'p'
	
#define MOVE_3_to_1 'q'
	
#define MOVE_3_to_2 'r'
	
 
	
char a[500], b[500], c[500];
	
int lena, lenb, lenc;
	
int i;
	
 
	
int  main()
	
{
	
	int T;
	
	in >> T;
	
	while (T--)
	
	{
	
		in >> a;
	
		in >> b;
	
		in >> c;
	
		//pas1
	
		lena = strlen(a);
	
		lenb = strlen(b);
	
		lenc = strlen(c);
	
 
	
		while (lena > 0) {
	
			out << MOVE_1_to_3;
	
			c[lenc++] = a[--lena];
	
			a[lena] = '\0';
	
		}
	
 
	
		while (lenb > 0) {
	
			out << MOVE_2_to_3;
	
			c[lenc++] = b[--lenb];
	
			b[lenb] = '\0';
	
		}
	
 
	
		//pas2
	
 
	
		while (lenc > 0) {
	
			if (c[--lenc] == 'c') {
	
				out << MOVE_3_to_2;
	
				b[lenb++] = c[lenc];
	
			}
	
			else {
	
				out << MOVE_3_to_1;
	
				a[lena++] = c[lenc];
	
			}
	
			c[lenc] = '\0';
	
		}
	
 
	
		//pas 3
	
 
	
		while (lenb > 0) {
	
			out << MOVE_2_to_3;
	
			c[lenc++] = b[--lenb];
	
			b[lenb] = '\0';
	
		}
	
		//pas 4
	
 
	
		while (lena > 0) {
	
			if (a[--lena] == 'b') {
	
				out << MOVE_1_to_2;
	
				b[lenb++] = a[lena];
	
			}
	
			else {
	
				out << MOVE_1_to_3;
	
				c[lenc++] = a[lena];
	
			}
	
			a[lena] = '\0';
	
		}
	
 
	
		//pas 5
	
 
	
		while (lenc > 0) {
	
			if (c[--lenc] == 'a') {
	
				out << MOVE_3_to_1;
	
				a[lena++] = c[lenc];
	
				c[lenc] = '\0';
	
			}
	
			else {
	
				break;
	
			}
	
		}
	
 
	
        out<<'\n';
	
	}
	
}
