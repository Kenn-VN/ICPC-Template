#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;

#define fi first
#define se second
#define NAME ""

const int INF = 1e9 + 7;
const int N = 2e5 + 1;
const int MOD = 1e9 + 7;

int n, q;

int root[N], sz[N];

struct DSU
{
    void make_set()
    {
        for (int u = 1; u <= n; u++)
        {
            sz[u] = 1;
            root[u] = u;
        }
    }

    int find_root(int u)
    {
        if (u == root[u]) return u;
        return root[u] = find_root(root[u]);
    }

    bool same_set(int u, int v)
    {
        u = find_root(u), v = find_root(v);
        return (u == v);
    }

    void join(int u, int v)
    {
        u = find_root(u), v = find_root(v);
        if (u == v) return;

        if (sz[u] < sz[v]) swap(u, v);
        sz[u] += sz[v];
        root[v] = u;
    }

} DSU;

void SOLVE()
{
    DSU.make_set();
    while (q--)
    {
        int req; cin >> req;
        if (req == 1)
        {
            int u, v; cin >> u >> v;
            DSU.join(u, v);
        }
        else
        {
            int u, v; cin >> u >> v;
            if (DSU.same_set(u, v)) cout << "YES \n";
                else cout << "NO \n";
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    if (fopen(NAME ".INP", "r"))
    {
        freopen(NAME ".INP", "r", stdin);
        freopen(NAME ".OUT", "w", stdout);
    }

    cin >> n >> q;

    SOLVE();
    return 0;
}