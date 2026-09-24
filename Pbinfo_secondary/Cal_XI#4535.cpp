#include <bits/stdc++.h>
using namespace std;

#define N_MAX 10
#define M_MAX 10
#define NM_MAX (N_MAX * M_MAX)

int main()
{
    struct poz
    {
        int l, c;
    } sol[NM_MAX + 1];
    int n, m, k = 1;
    int d[NM_MAX + 1], dl[] = {-2, -2, -1, 1, 2, 2, 1, -1}, dc[] = {-1, 1, 2, 2, 1, -1, -2, -2};
    int nr_pioni_ramasi, nr_pioni = 0, nr_minim_pasi = INT32_MAX, nr_solutii = 0;
    int a[N_MAX + 1][M_MAX + 1];
    int vizitat[N_MAX + 1][M_MAX + 1]; // marcăm pozițiile vizitate

    // citire
    ifstream cin("cal_xi.in");
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            vizitat[i][j] = 0;
            cin >> a[i][j];
            if (a[i][j] == 1)
                nr_pioni++;
            if (a[i][j] == 2)
            {
                sol[k].l = i;
                sol[k].c = j;
            }
        }
    vizitat[sol[k].l][sol[k].c] = 1; // marcăm poziția de start ca vizitată
    nr_pioni_ramasi = nr_pioni;
    // gasire solutii
    int cont;
    k++; // urmatoarea pozitie
    d[k] = -1;

    while (k > 1)
    {
        if (d[k] < 7)
        {
            // verific directia urmatoare
            d[k]++;
            sol[k].l = sol[k - 1].l + dl[d[k]];
            sol[k].c = sol[k - 1].c + dc[d[k]];

            cont = 1;
            if (a[sol[k].l][sol[k].c] == 3)
                cont = 0;
            else if (vizitat[sol[k].l][sol[k].c]) // deja vizitat
                cont = 0;
            else if (sol[k].l < 1 || sol[k].l > n || sol[k].c < 1 || sol[k].c > m)
                cont = 0;
            if (cont)
            {
                // pozitie valida
                // actualizare pioni ramasi
                if (a[sol[k].l][sol[k].c] == 1)
                    nr_pioni_ramasi--;

                if (nr_pioni_ramasi == 0)
                {
                    nr_solutii++;
                    if (k < nr_minim_pasi)
                        nr_minim_pasi = k;
                    // dupa ce am gasit o solutie:
                    //  trebuie restaurat:
                    // 1. pionii ramasi
                    if (a[sol[k].l][sol[k].c] == 1)
                        nr_pioni_ramasi++;
                    // 2. demarcăm poziția
                    vizitat[sol[k].l][sol[k].c] = 0;
                }
                else
                {
                    // cu toate ca este o pozitie valida, nu este finalizata gasirea unei solutii
                    // marchez pozitia k ca fiind vizitata
                    vizitat[sol[k].l][sol[k].c] = 1;
                    //  si trec la urmatoarea pozitie
                    k++;
                    d[k] = -1;
                }
            }
        }
        else
        {
            // nu mai am directii de verificat
            //  si revin la pozitia anterioara
            k--;
            //  trebuie restaurat:
            // 1. pionii ramasi
            if (a[sol[k].l][sol[k].c] == 1)
                nr_pioni_ramasi++;
            // 2. demarcăm poziția
            vizitat[sol[k].l][sol[k].c] = 0;
        }
    }
    // afisare
    ofstream cout("cal_xi.out");
    if (nr_solutii <= 0)
        cout << "IMPOSIBIL";
    else
        cout << nr_solutii << ' ' << nr_minim_pasi - 1; // pornesc de la 0
    cout << endl;
}