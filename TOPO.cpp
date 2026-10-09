#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;

#define fi first
#define se second
#define NAME "TEST"

const int inf = 1e9 + 7;
const ll INF = 1e18 + 7;
const int N = 2e5 + 1;
const int MOD = 1e9 + 7;

int n, m;
vector<int> g[N];
bool visited[N];
vector<int> topo;

void DFS(int u)
{
    visited[u] = true;
    for (int v : g[u])
    {
        if (visited[v]) continue;
        DFS(v);
    }
    topo.push_back(u);
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

    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
    }

    for (int u = 1; u <= n; u++)
    {
        if (visited[u]) continue;
        DFS(u);
    }
    reverse(topo.begin(), topo.end());
    for (auto u : topo) cout << u << " ";

    return 0;
}