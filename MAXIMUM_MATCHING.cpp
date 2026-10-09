#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pli = pair<ll, int>;

#define fi first
#define se second
#define NAME "FMATCH"

const int smallINF = 2e9 + 7;
const ll INF = 2e18 +7;
const int N = 2e5;
const int smallN = 2e3 + 2;
const int MOD = 1e9 + 7;

int n, m, p, cap[smallN + 1][smallN + 1];
vector<int> adj[smallN + 1];

int bfs(int st, int ed, vector<int> &par)
{
    fill(par.begin(), par.end(), 0);
    par[st] = -1;
    queue<pii> q;
    q.push({st, smallINF});
    
    while (!q.empty())
    {
        auto top = q.front(); q.pop();
        int curr = top.fi, flow = top.se;
        for (int next : adj[curr])
        {
            if (par[next] != 0 || cap[curr][next] == 0) continue;
            par[next] = curr;
            int new_flow = min(flow, cap[curr][next]);
            if (next == ed) return new_flow;
            q.push({next, new_flow});
        }
    }

    return 0;
}

int max_flow(int st, int ed)
{
    vector<int> par(n + m + 2);
    int flow = 0;
    int new_flow;

    while (new_flow = bfs(st, ed, par))
    {
        flow += new_flow;
        int curr = ed;
        while (curr != st)
        {
            int prev = par[curr];
            cap[prev][curr] -= new_flow;
            cap[curr][prev] += new_flow;
            curr = prev;
        }
    }   

    return flow;
}

void SOLVE()
{
    for (int u = 1; u <= n; u++)
    {
        adj[0].push_back(u);
        adj[u].push_back(0);
        cap[0][u] = 1;
    }
    for (int u = n + 1; u <= n + m; u++)
    {
        int v = n + m + 1;
        adj[u].push_back(v);
        adj[v].push_back(u);
        cap[u][v] = 1;
    }
    cout << max_flow(0, n + m + 1);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    //freopen(NAME ".inp", "r", stdin);
    //freopen(NAME ".out", "w", stdout);
    cin >> n >> m >> p;
    for (int i = 1; i <= p; i++)
    {
        int u, v; cin >> u >> v;
        v = v + n;
        adj[u].push_back(v);
        adj[v].push_back(u);
        cap[u][v] = 1;
    }
    SOLVE();
    return 0;
}
