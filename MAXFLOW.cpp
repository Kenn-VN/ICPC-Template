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
const int N = 1001;
const int MOD = 39 + 7;

int n, m, s, t, capacity[N][N];
vector<int> g[N];

int BFS(int st, int ed, vector<int> &par)
{
    fill(par.begin(), par.end(), 0);
    par[st] = -1;
    queue<pii> q;
    q.push({st, smallINF});

    while (!q.empty())
    {
        auto top = q.front(); q.pop();
        int u = top.fi, flow = top.se;
        for (int v : g[u])
        {
            if (par[v] != 0 || capacity[u][v] == 0) continue;
            par[v] = u;
            int new_flow = min(flow, capacity[u][v]);
            if (v == ed) return new_flow;
            q.push({v, new_flow});
        }
    }
    return 0;
}

int max_flow(int st, int ed)
{
    vector<int> par(n + 1);
    int flow = 0;
    int new_flow;

    while (new_flow = BFS(st, ed, par))
    {
        flow += new_flow;
        int curr = ed;
        while (curr != st)
        {
            int prev = par[curr];
            capacity[prev][curr] -= new_flow;
            capacity[curr][prev] += new_flow;
            curr = prev; 
        }
    }

    return flow;
}

void SOLVE()
{
    cout << max_flow(s, t);
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

    cin >> n >> m >> s >> t;
    for (int i = 1; i <= m; i++)
    {
        int u, v, w; cin >> u >> v >> w;
        g[u].push_back(v);
        g[v].push_back(u);
        capacity[u][v] = w;
    }

    SOLVE();
    return 0;
}
