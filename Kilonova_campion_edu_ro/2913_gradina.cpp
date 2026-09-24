#include <bits/stdc++.h>

using namespace std;

struct Point
{
    int x, y;
};

typedef map<char, bool> Fences;
typedef vector<Point> Coordonates;

const vector<pair<char, int>> fences = {
    // descending
    {'S', 8},
    {'E', 4},
    {'N', 2},
    {'V', 1},
};

int max_decode = accumulate(fences.begin(), fences.end(), 0,
                            [](int acc, const auto &p)
                            { return acc + p.second; });

const map<char, Point> directions = {
    {'V', {0, -1}},
    {'N', {-1, 0}},
    {'E', {0, +1}},
    {'S', {+1, 0}},
};

struct RemovedFence
{
    Point location;
    char fence;
};

template <class T>
class Matrix
{
public:
    vector<vector<T>> matrix;

    T &operator[](Point p)
    {
        return matrix[p.x][p.y];
    }

    const T &operator[](Point p) const
    {
        return matrix[p.x][p.y];
    }
};

class Garden
{
public:
    Matrix<Fences> garden;
    Matrix<int> zones;

    Coordonates xOy = {};
    int n = 0, m = 0, species = 0;
    const int empty_value = -1;

    bool _in_zone(Point &p, char direction)
    {
        bool fence = garden[p][direction];
        return !fence;
    }

    bool _is_empty(Point &p)
    {
        return zones[p] == empty_value;
    }

    void _zone_fill(Point a)
    {
        Point nxt;

        zones[a] = species;

        for (const auto &[fence_loc, fence_coords] : directions)
        {
            nxt = {a.x + fence_coords.x, a.y + fence_coords.y};
            if (inside(nxt) && _in_zone(a, fence_loc) && _is_empty(nxt))
            {
                _zone_fill(nxt);
            }
        }
    }

    void _init_garden(const int rows, const int cols)
    {
        Point c;
        int i, j;

        n = rows;
        m = cols;

        garden.matrix.resize(n);
        zones.matrix.resize(n);
        for (i = 0; i < n; ++i)
        {
            garden.matrix[i].resize(m);
            zones.matrix[i].resize(m, empty_value);
            for (j = 0; j < m; ++j)
            {
                c = {i, j};
                xOy.push_back(c);
                for (const auto &[fence_loc, _] : directions)
                {
                    garden[c][fence_loc] = 0;
                }
            }
        }
    }

    bool inside(Point &p)
    {
        bool ans = true;
        if (p.x < 0 || n - 1 < p.x)
            ans = false;
        if (p.y < 0 || m - 1 < p.y)
            ans = false;
        return ans;
    }

    void fill(void)
    {
        species = empty_value;
        for (Point a : xOy)
        {
            if (_is_empty(a))
            {
                // start to fill a new zone
                ++species; // are numbered from 0
                _zone_fill(a);
            }
        }
        ++species;
    }

    Fences &operator[](Point p)
    {
        return garden[p];
    }

    const Fences &operator[](Point p) const
    {
        return garden[p];
    }
};

struct Problem
{
    Garden G; // todo: use inheritance
    vector<int> areas = {};
    const char not_found = 'X';
    int merged_area = 0;
    RemovedFence rf = {{0, 0}, not_found};

    void _read_garden_dimensions(void)
    {
        int n = 0, m = 0;
        const Point upr_lim = {20, 20}, lwr_lim = {1, 1};
        cin >> n >> m;
        assert(lwr_lim.x <= n && n <= upr_lim.x);
        assert(lwr_lim.y <= m && m <= upr_lim.y);
        G._init_garden(n, m);
    }

    void _read_garden_cells()
    {
        int cell = 0; // a cell with no borders
        for (Point p : G.xOy)
        {
            cin >> cell;
            assert(cell <= max_decode);
            for (const auto [name, value] : fences)
            {
                if (cell - value >= 0)
                {
                    cell -= value;
                    G[p][name] = 1;
                }
            }
        }
    }

    int _get_max_areas()
    {
        int max_area = 0;
        areas.resize(G.species);
        for (Point p : G.xOy)
        {
            areas[G.zones[p]] += 1;
        }

        max_area = *max_element(areas.begin(), areas.end());
        return max_area;
    }

    void _update_removed_fence(int new_area, Point cell, char fence_location)
    {
        Point location = {cell.x + 1, cell.y + 1};

        if (new_area > merged_area)
        {
            // area, row, column and border to be deleted
            merged_area = new_area;
            // position starts from 1
            rf.location = location;
            rf.fence = fence_location;
        }
        else if (new_area == merged_area)
        {
            if (location.x < rf.location.x)
            {
                rf.location = location;
                rf.fence = fence_location;
            }
            else if (rf.location.x == location.x)
            {
                if (location.y < rf.location.y)
                {
                    rf.location = location;
                    rf.fence = fence_location;
                }
                else if (location.y == rf.location.y)
                {
                    if (fence_location == 'N')
                    {
                        rf.fence = 'S';
                    }
                    else if (fence_location == 'V')
                    {
                        rf.fence = 'E';
                    }
                    else
                    {
                        // no change in area, location and border
                    }
                }
                else
                { // no new minimum column
                }
            }
            else
            { // no new minimum row
            }
        }
        else
        {
            // no new maximum area
        }
    }

    void _merge_2neighbours(void)
    {
        int zone1, zone2, new_area;
        Point ngb;

        for (Point a : G.xOy)
        {
            for (const auto &[fence_loc, fence_coord] : directions)
            {
                ngb = {a.x + fence_coord.x, a.y + fence_coord.y};
                if (G.inside(ngb))
                {
                    zone1 = G.zones[a];
                    zone2 = G.zones[ngb];
                    if (zone1 != zone2 && G.garden[a][fence_loc]) // not in a zone
                    {
                        new_area = areas[zone1] + areas[zone2];
                        _update_removed_fence(new_area, a, fence_loc);
                    }
                }
            }
        }
    }

    void run(void)
    {
        _read_garden_dimensions();
        _read_garden_cells();
        G.fill();
        cout << G.species << endl;

        cout << _get_max_areas() << endl;

        if (G.species > 1)
        {
            _merge_2neighbours();
        }

        cout << merged_area << ' ';
        cout << rf.location.x << ' ';
        cout << rf.location.y << ' ';
        cout << rf.fence << endl;
    }
};

int main()
{
    Problem p;
    FILE *fin = freopen("gradina.in", "r", stdin);
    FILE *fout = freopen("gradina.out", "w", stdout);
    p.run();
    fclose(fin);
    fclose(fout);
    return 0;
}