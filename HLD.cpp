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

int n, q, a[N], par[N], depth[N], sz[N];
vector<int> g[N];

struct SMT
{
    int tree[N * 4];

    void UPDATE(int pos, int val, int id = 1, int l = 1, int r = n)
    {
        if (l > pos || r < pos) return;
        if (l == r) 
        {
            tree[id] = val;
            return;
        }

        int mid = (l + r) / 2;
        UPDATE(pos, val, id * 2, l, mid);
        UPDATE(pos, val, id * 2 + 1, mid + 1, r);
        tree[id] = max(tree[id * 2], tree[id * 2 + 1]);
    }

    int GET(int u, int v, int id = 1, int l = 1, int r = n)
    {
        if (v < l || u > r) return 0;
        if (u <= l && r <= v) return tree[id];

        int mid = (l + r) / 2;
        int NODELEFT = GET(u, v, id * 2, l, mid);
        int NODERIGHT = GET(u, v, id * 2 + 1, mid + 1, r);
        return max(NODELEFT, NODERIGHT);
    }

} SMT;

struct HLD
{
    void DFS(int u, int prev = 0)
    {
        sz[u] = 1;
        par[u] = prev;
        depth[u] = depth[prev] + 1;
        for (int v : g[u])
        {
            if (v == prev) continue;
            DFS(v, u);
            sz[u] += sz[v];
        }
    }

    int head[N], id[N], pos[N], cur_chain = 1, cur_pos = 1; 

    void BUILD_CHAIN(int u, int prev = 0)
    {
        if (head[cur_chain] == 0) head[cur_chain] = u;
        id[u] = cur_chain;
        pos[u] = cur_pos;
        cur_pos++;

        int next = 0;
        for (int v : g[u])
        {
            if (v == prev) continue;
            if (next == 0 || sz[v] > sz[next]) next = v;
        }
        if (next != 0) BUILD_CHAIN(next, u);

        for (int v : g[u])
        {
            if (v == prev || v == next) continue;
            cur_chain++;
            BUILD_CHAIN(v, u);
        }
    }

    int FIND_LCA(int u, int v)
    {
        while (id[u] != id[v])
        {
            if (id[u] > id[v]) u = par[head[id[u]]];
                else v = par[head[id[v]]];
        }
        if (depth[u] < depth[v]) return u;
        return v;
    }

    void UPDATE(int u, int val)
    {
        SMT.UPDATE(pos[u], val);
    }

    int QUERY(int u, int v)
    {
        int LCA = FIND_LCA(u, v);
        int res = 0;

        while (id[u] != id[LCA])
        {
            res = max(res, SMT.GET(pos[head[id[u]]], pos[u]));
            u = par[head[id[u]]];
        }

        while (id[v] != id[LCA])
        {
            res = max(res, SMT.GET(pos[head[id[v]]], pos[v]));
            v = par[head[id[v]]];
        }

        if (depth[u] < depth[v]) res = max(res, SMT.GET(pos[u], pos[v]));
            else res = max(res, SMT.GET(pos[v], pos[u]));

        return res;
    }

} HLD;

void SOLVE()
{
    HLD.DFS(1);
    HLD.BUILD_CHAIN(1);

    for (int i = 1; i <= n; i++) HLD.UPDATE(i, a[i]);
    
    while (q--)
    {
        int type; cin >> type;
        if (type == 1)
        {
            int u, x; cin >> u >> x;
            HLD.UPDATE(u, x);
        }
        else
        {
            int u, v; cin >> u >> v;
            cout << HLD.QUERY(u, v) << "\n";
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
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i < n; i++)
    {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    SOLVE();
    return 0;
}