#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;

#define fi first
#define se second
#define NAME ""

const int smallINF = 2e9 + 7;
const ll INF = 2e18 + 7;
const int N = 2e5 + 5;
const int MOD = 1e9 + 7;

int n, m;
vector<ll> d;
vector<int> trace;
vector<pli> g[N];

void dijkstra(int st)
{
    d.resize(n + 1, INF);
    trace.resize(n + 1);
    d[1] = 0;   
    priority_queue<pli, vector<pli>, greater<pli>> q;
    q.push({0, st});
    while (!q.empty())
    {
        auto top = q.top(); q.pop();
        int u = top.se; ll dist = top.fi;
        if (dist != d[u]) continue;
        for (auto it : g[u])
        {
            int v = it.se; ll w = it.fi;
            if (d[v] > d[u] + w)
            {
                d[v] = d[u] + w;
                trace[v] = u;
                q.push({d[v], v});
            }
        }
    }
}

void SOLVE()
{
    dijkstra(1);
    if (d[n] == INF)
    {
        cout << "-1 \n";
        return;
    }
    cout << d[n] << "\n";
    vector<int> path;
    while (n != 1)
    {
        path.push_back(n);
        n = trace[n];
    }
    path.push_back(1);
    for (int i = path.size() - 1; i >= 0; i--) cout << path[i] << " ";
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
        int u, v, w; cin >> u >> v >> w;
        g[u].push_back({w, v});
        g[v].push_back({w, u});
    }

    SOLVE();
    return 0;
}