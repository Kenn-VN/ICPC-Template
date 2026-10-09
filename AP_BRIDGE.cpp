//Given a undirected graph with n vertices and m edges, count the number of articulation points and bridges in the graph.

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

int n, m, num[N], low[N];
vector<int> g[N];
pii E[N];
bool used[N], check_bridge[N], check_ap[N];

vector<int> res;

int timeDFS = 0;
void DFS(int u, int prev = 0)
{
    timeDFS++;
    low[u] = num[u] = timeDFS;
    int child = 0;

    for (int id : g[u])
    {
        if (used[id]) continue;
        used[id] = true;
        int v = E[id].fi + E[id].se - u;
        if (num[v] == 0)
        {
            child++;
            DFS(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= num[v]) check_bridge[id] = true;
            if (low[v] >= num[u] and prev != 0) check_ap[u] = true;
        }
        else low[u] = min(low[u], num[v]);
    }

    if (prev == 0 and child > 1) check_ap[u] = true;
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
        E[i] = {u, v};
        g[u].push_back(i);
        g[v].push_back(i);
    }

    for (int u = 1; u <= n; u++)
        if (num[u] == 0) DFS(u);

    int cnt_bridge = 0, cnt_ap = 0;
    for (int i = 1; i <= m; i++) cnt_bridge += check_bridge[i];
    for (int u = 1; u <= n; u++) cnt_ap += check_ap[u];
    cout << cnt_ap << " " << cnt_bridge << "\n";

    return 0;
}