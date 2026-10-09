#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pli = pair<ll, int>;

#define fi first
#define se second

const int N = 1000;
const int level = 18;

int n, q, par[N + 1][level + 1], h[N + 1];
vector<pli> adj[N + 1];
ll dist[N + 1];

void dfs(int u, int prev)
{
    h[u] = h[prev] + 1;
    if (u == 1) par[u][0] = 1;
        else par[u][0] = prev;
    for (auto it : adj[u])
    {
        ll w = it.fi;
        int v = it.se;
        if (v == prev) continue;
        dist[v] = dist[u] + w;
        dfs(v, u);
    }
}

void build_ST()
{
    for (int i = 1; i <= level; i++)
        for (int u = 1; u <= n; u++) par[u][i] = par[par[u][i - 1]][i - 1];
}

int lca(int u, int v)
{
    if (h[u] > h[v]) swap(u, v);
    int diff = h[v] - h[u];
    for (int i = 0; i <= level; i++)
        if ((1 << i) & diff) v = par[v][i];
    if (u == v) return u;
    for (int i = level; i >= 0; i--)
    {
        if (par[u][i] != par[v][i])
        {
            u = par[u][i];
            v = par[v][i];
        }
    }
    return par[u][0];
}

ll find_dis(int u, int v)
{
    int LCA = lca(u, v);
    return dist[u] + dist[v] - 2 * dist[LCA];
}

void solve()
{
    dfs(1, 0);
    build_ST();
    while (q--)
    {
        int u, v; cin >> u >> v;
        cout << find_dis(u, v) << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> q;
    for (int i = 1; i < n; i++)
    {
        int u, v; ll w;
        cin >> u >> v >> w;
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
    }
    solve();
    return 0;
}
