//Determine for each node the sum of the distances from the node to all other nodes.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;

#define fi first
#define se second

const int inf = 1e9 + 7;
const ll INF = 1e18 + 7;
const int N = 2e5 + 1;
const int MOD = 1e9 + 7;

int n, sz[N];
ll d[N];
vector<int> g[N];

void DFS(int u, int prev = 0)
{
    sz[u] = 1;
    for (int v : g[u])
    {
        if (v == prev) continue;
        DFS(v, u);
        sz[u] += sz[v];
        d[u] += d[v] + sz[v];
    }
}

void REROOT(int u, int prev = 0)
{
    for (int v : g[u])
    {
        if (v == prev) continue;
        d[v] = d[u] - sz[v] + n - sz[v];
        REROOT(v, u);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    DFS(1);
    REROOT(1);

    for (int u = 1; u <= n; u++) cout << d[u] << " "; cout << "\n";

    return 0;
}