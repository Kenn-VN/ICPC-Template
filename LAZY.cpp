#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;

#define fi first
#define se second
#define NAME "TEST"

const ll INF = 1e18 + 7;
const int N = 1e5 + 1;
const int MOD = 1e9 + 7;

int n, q, a[N];

struct SMT
{
    ll tree[4 * N], lazy[4 * N];

    void PLAZY(int id, int l, int r)
    {
        if (lazy[id] == 0) return;
        tree[id] += lazy[id];

        if (l != r)
        {
            lazy[id * 2] += lazy[id];
            lazy[id * 2 + 1] += lazy[id];
        }

        lazy[id] = 0;
    }

    void UPDATE(int u, int v, int val, int id = 1, int l = 1, int r = n)
    {
        PLAZY(id, l, r);
        if (v < l or u > r) return;
        if (u <= l and r <= v)
        {
            lazy[id] += val;
            PLAZY(id, l, r);
            return;
        }

        int mid = (l + r) / 2;
        UPDATE(u, v, val, id * 2, l, mid);
        UPDATE(u, v, val, id * 2 + 1, mid + 1, r);
        tree[id] = min(tree[id * 2], tree[id * 2 + 1]);
    }

    ll GET(int u, int v, int id = 1, int l = 1, int r = n)
    {
        PLAZY(id, l, r);
        if (v < l or u > r) return INF;
        if (u <= l and r <= v) return tree[id];

        int mid = (l + r) / 2;
        return min(GET(u, v, id * 2, l, mid), GET(u, v, id * 2 + 1, mid + 1, r));
    }

} SMT;

void SOLVE()
{
    for (int i = 1; i <= n; i++) SMT.UPDATE(i, i, a[i]);
    while (q--)
    {
        int type; cin >> type;
        if (type == 1)
        {
            int u, v, val; cin >> u >> v >> val;
            SMT.UPDATE(u, v, val);
        }
        else
        {
            int l, r; cin >> l >> r;
            cout << SMT.GET(l, r) << "\n";
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

    SOLVE();
    return 0;
}