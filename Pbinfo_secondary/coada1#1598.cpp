#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Problema
{
    queue<int> q;
    vector<int> result;

    void afisare()
    {
        for (auto x : result)
            cout << x << "\n";
    }

    void push(int x)
    {
        queue<int> q_aux = q;
        bool found = false;
        while (!q_aux.empty() && !found)
        {
            if (q_aux.front() == x)
                found = true;
            q_aux.pop();
        }
        if (found)
            q = q_aux;
        q.push(x);
    }

    void query(int x)
    {
        queue<int> q_aux = q;
        int poz = 1;
        bool found = false;
        while (!q_aux.empty())
        {
            if (q_aux.front() == x)
                found = true;
            if (!found)
                ++poz;
            q_aux.pop();
        }

        if (!found)
            poz = -1;

        result.push_back(poz);
    }

    void calcul()
    {
        int M = 0;
        int num = 0;
        string s = "";
        cin >> M;
        while (M--)
        {
            cin >> s;
            cin >> num;
            if (s == "push")
                push(num);
            else if (s == "query")
                query(num);
        }
    }
};

int main()
{
    freopen("C:\\Users\\acasa\\Desktop\\pbinfo\\coada1.in", "r", stdin);
    freopen("C:\\Users\\acasa\\Desktop\\pbinfo\\coada1.out", "w", stdout);
    Problema p;
    p.calcul();
    p.afisare();
    fclose(stdin);
    fclose(stdout);
    return 0;
}