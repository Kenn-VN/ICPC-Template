#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;

#define fi first
#define se second
#define NAME "TEST"

const int INF = 1e9 + 7;
const int N = 1e5 + 1;
const int MOD = 1e9 + 7;

int n, q, a[N];

struct SMT
{
    ll tree[4 * N];

    void UPDATE(int pos, int val, int id = 1, int l = 1, int r = n)
    {
        if (pos < l or pos > r) return;
        if (l == r)
        {
            tree[id] = val;
            return;
        }

        int mid = (l + r) / 2;
        UPDATE(pos, val, id * 2, l, mid);
        UPDATE(pos, val, id * 2 + 1, mid + 1, r);
        tree[id] = tree[id * 2] + tree[id * 2 + 1];
    }

    ll GET(int u, int v, int id = 1, int l = 1, int r = n)
    {
        if (v < l or u > r) return 0;
        if (u <= l and r <= v) return tree[id];

        int mid = (l + r) / 2;
        return GET(u, v, id * 2, l, mid) + GET(u, v, id * 2 + 1, mid + 1, r);
    }

} SMT;

void SOLVE()
{
    for (int i = 1; i <= n; i++) SMT.UPDATE(i, a[i]);
    while (q--)
    {
        int type; cin >> type;
        if (type == 1)
        {
            int pos, val; cin >> pos >> val;
            SMT.UPDATE(pos, val);
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