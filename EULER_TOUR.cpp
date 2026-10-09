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

int n, q, diff[N], st[N], ed[N];
vector<int> g[N];

int timeDFS = 0;
void DFS(int u, int prev)
{
    timeDFS++;
    st[u] = timeDFS;
    
    for (int v : g[u])
    {
        if (v == prev) continue;
        DFS(v, u);
    }

    ed[u] = timeDFS;
}

struct FENWICK_TREE
{
    int BIT[N];

    void update(int id, int val)
    {
        while (id <= timeDFS)
        {
            BIT[id] += val;
            id += (id & (-id));
        }
    }

    int get_prefix(int id)
    {
        int res = 0;
        while (id > 0)
        {
            res += BIT[id];
            id -= (id & (-id));
        }
        return res;
    }

} F;

void SOLVE()
{
    DFS(1, 0);
    while (q--)
    {
        int u, val; cin >> u >> val;
        F.update(st[u], val);
        F.update(ed[u] + 1, -val);
    }
    for (int u = 1; u <= n; u++) cout << F.get_prefix(st[u]) << " ";
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
    for (int i = 1; i < n; i++)
    {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    SOLVE();
    return 0;
}