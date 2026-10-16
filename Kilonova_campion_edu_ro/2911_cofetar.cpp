#include <bits/stdc++.h>

using namespace std;

#define MIN_INGREDIENTS 1
#define MAX_INGREDIENTS 30
#define MIN_PRICE 0
#define MAX_PRICE 1000
#define MIN_PROPORTION 0
#define MAX_PROPORTION 100

struct Pair {
    int value;
    int loc;
};

struct Cofetar
{
    int N = 0; // no. all ingredients
    vector<int> raw_prices;
    int k = 0; // no. restrictions
    vector<int> raw_restrictions_x;
    vector<int> raw_restrictions_y;
    int m = 0; // no. ingredients in use
    vector<int> raw_proportions;

    vector<Pair> prices;
    /* Ingredients prices are ordered, thus a cheap ingredient will be used first.
    Pair.loc represents it's original location.
    */
    vector<unsigned int> restrictions;
    /* matrix contains input restrictions and ingredients in use
    each row is a bit field. bit location correlates to ingredient location
    for an ingredient i, bits (other ingredients) values are restricted = 1 or compatible = 0
    */
    vector<Pair> proportions;
    /* Proportions are in a descending order.
    Therefore a cheap ingredient will be used in a higher proportion.*/
    vector<int> sums;

    // backtracking:
    int n = 0; // max location
    vector<int> stack_ing_cost; // ingredients in use, sum of their prices
    vector<int> stack_ing_pos; // ingredients in use, location in ordered prices
    vector<unsigned int> stack_ings_restricted; 
    // an element is a bit field. if a bit is set, ingredient is used or restricted.

    // output:
    int min_total_cost = INT_MAX;
    vector<int> ingredients; // their location
    string s_ingredients = ""; // to apply lexycographic order

    void _read(void)
    {
        int i = 0;
        int x;
        int y;

        cin >> N;
        assert(MIN_INGREDIENTS < N && N < MAX_INGREDIENTS);
        n = N;
        raw_prices.resize(n);
        while (i < n)
        {
            cin >> x;
            assert(MIN_PRICE < x && x < MAX_PRICE);
            raw_prices.at(i) = x;
            ++i;
        }

        i = 0;
        cin >> k;
        assert(0 <= k && k <= n * (n - 1));
        raw_restrictions_x.resize(k);
        raw_restrictions_y.resize(k);
        while (i < k)
        {
            cin >> x >> y;
            assert(MIN_INGREDIENTS <= x && x <= n);
            assert(MIN_INGREDIENTS <= y && y <= n);
            raw_restrictions_x.at(i) = x;
            raw_restrictions_y.at(i) = y;
            ++i;
        }

        i = 0;
        cin >> m;
        assert(MIN_INGREDIENTS < m && m < n);
        raw_proportions.resize(m);
        while (i < m)
        {
            cin >> x;
            assert(MIN_PROPORTION < x && x < MAX_PROPORTION);
            raw_proportions.at(i) = x;
            ++i;
        }
    }

    void _calculate_sum()
    {
        int i = 0;
        sums.resize(n);
        while (i < n)
        {
            int sum = 0;
            int nr = restrictions.at(i);
            if (nr)
                do sum++; while (nr &= nr - 1);
            sums.at(i) = sum;
            ++i;
        }
    }

    void _erase(int i)
    {
        prices.erase(next(prices.begin(), i));
        sums.erase(next(sums.begin(), i));
        // restrictions erase
        // column erase
        int j = 0;
        while (j < n)
        {
            restrictions.at(j) &= ~(1 << i);
            ++j;
        }
        // row erase
        j = i + 1;
        while (j < n)
        {
            restrictions.at(j) >>= 1;
            ++j;
        }
        restrictions.erase(next(restrictions.begin(), i));
    }

    void _prep(void)
    {
        /* example:

        prices       50 20 70 90 30 100
        loc          0  1  2  3  4  5
        ordered_loc  2  0  3  4  1  5

        ordered      20 30 50 70 90 100
        loc          0  1  2  3  4  5
        original_loc 1  4  0  2  3  5

        proportions  30 20 40 10
        loc          0  1  2  3
        ordered      1  2  0  3

        ordered      40 30 20 10
        loc          0  1  2  3
        original     2  0  1  3

        restrictions
        original       ordered
        1 3	 0 2       2 3
        1 5	 0 4       2 4
        3 4	 2 3       3 4
        3 5	 2 4       3 1

        */

        int i = 0;
        int j;
        int i_ordered = 0;
        Pair p;
        // order prices
        vector<Pair> unordered_prices(n);
        prices.resize(n);
        while (i < n)
        {
            p.value = raw_prices.at(i);
            p.loc = i;
            prices.at(i) = p;
            ++i;
        }
        stable_sort(prices.begin(), prices.end(),
            [](Pair a, Pair b)
            {
                return a.value < b.value;
            }
        );
        while (i_ordered < n)
        {
            i = prices[i_ordered].loc;
            p.value = raw_prices.at(i);
            p.loc = i_ordered;
            unordered_prices.at(i) = p;
            ++i_ordered;
        }
        // init restrictions
        restrictions.resize(n, 0u);
        i = 0;
        while (i < n)
        {
            restrictions.at(i) |= (1 << i); // restriction to reuse an ingredient
            ++i;
        }
        // update restrictions
        i = 0;
        while (i < k)
        {
            i_ordered = unordered_prices[raw_restrictions_x.at(i) - 1].loc;
            int j_ordered = unordered_prices[raw_restrictions_y.at(i) - 1].loc;
            restrictions.at(i_ordered) |= (1 << j_ordered);
            restrictions.at(j_ordered) |= (1 << i_ordered);
            ++i;
        }
        // clean up ingredients:
        // try to remove extra, n - m expensive ingredients; modify prices and restrictions to be of size m
        _calculate_sum();
        // an ingredient is removed when it has many restrictions, such that m ingredients cannot be used.
        i = 0;
        while (i < n)
        {
            if (n - sums[i] < m - 1)
            {
                _erase(i);
                --n;
                _calculate_sum();
            }
            else
                ++i;
        }
        // TBD? ingredient with same ammount of restrictions, with higher price is removed
        i = 0;
        proportions.resize(m);
        while (i < m)
        {
            p.value = raw_proportions.at(i);
            p.loc = i;
            proportions.at(i) = p;
            ++i;
        }

        stable_sort(proportions.begin(), proportions.end(),
            [](Pair a, Pair b)
            {
                return a.value > b.value;
            }
        );
        ingredients.resize(m);
    }
    
    void _save(void)
    {
        /*
        solution example:
        0  1  4  5
        20 30 90 100
        2  5  4  6
        and rearanged to keep proportions locations:
        5  4  2  6
        */
        int i = 1;
        vector<int> new_answer(m);
        string new_sanswer = "";
        if (stack_ing_cost[m] < min_total_cost)
        {
            ingredients.clear();
        }
        min_total_cost = stack_ing_cost[m];
        while (i <= m)
        {
            new_answer.at(proportions[i - 1].loc) = prices[stack_ing_pos[i]].loc + 1;
            ++i;
        }
        ingredients = new_answer;
        /*
        i = 0;
        while (i < m)
        {
            new_sanswer += (char)new_answer[i];
            ++i;
        }
        if (ingredients.empty())
        {
            ingredients = new_answer;
            s_ingredients = new_sanswer;
        }
        else if (new_sanswer > s_ingredients)
        {
            ingredients = new_answer;
            s_ingredients = new_sanswer;
        }*/
    }

    void _bkt(void)
    {
        int i;
        int sp = 1; // sp start from 1, stack[0]= 0 and sp-1 works
        stack_ings_restricted.resize(m + 1, 0);
        stack_ing_pos.resize(m + 1, 0);
        stack_ing_cost.resize(m + 1, 0);

        stack_ing_pos[sp] = -1; // start from -1 because vectors start from 0 and bits are used 
        stack_ing_cost[sp] = 0;
        stack_ings_restricted[sp] = 0;

        while (sp > 0)
        {
            if (stack_ing_pos[sp] < n - 1)
            {
                ++stack_ing_pos[sp];
                int valid = true;
                if(valid)
                {
                    // check compatibilities
                    stack_ings_restricted[sp] = stack_ings_restricted[sp - 1];
                    if ((1 << stack_ing_pos[sp]) & stack_ings_restricted[sp])
                        valid = false;
                    stack_ings_restricted[sp] |= restrictions.at(stack_ing_pos[sp]);
                }
                if(valid)
                {
                    // check cost
                    stack_ing_cost[sp] = stack_ing_cost[sp - 1];
                    stack_ing_cost[sp] += proportions[sp - 1].value * prices[stack_ing_pos[sp]].value;
                    // check if price remains under minimum
                    if (stack_ing_cost[sp] > min_total_cost)
                        valid = false;
                }
                if(valid)
                {
                    // check if complete
                    if (sp == m)
                    {
                        _save();
                    }
                    else
                    {
                        ++sp;
                        stack_ing_pos[sp] = 0;
                    }
                }
            }
            else
            {
                --sp;
            }
        }
    }

    void _print(void)
    {
        int i = 0;
        assert(ingredients.size() > 0);
        cout << min_total_cost << endl;
        while (i < m)
        {
            cout << ingredients[i] << ' ';
            ++i;
        }
        cout << endl;
    }

    void run(void)
    {
        _read();
        _prep();
        _bkt();
        _print();
    }
};

int main()
{
    Cofetar c;
    FILE* fin = freopen("cofetar.in", "r", stdin);
    FILE *fout = freopen("cofetar.out", "w", stdout);

    c.run();

    fclose(fin);
    fclose(fout);
    return 0;
}