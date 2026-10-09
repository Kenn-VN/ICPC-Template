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
 
int n, q, a[N], MIN[N][21];
 
void BUILD_ST()
{
    for (int i = 1; i <= n; i++) MIN[i][0] = a[i];
    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            MIN[i][j] = min(MIN[i][j - 1], MIN[i + (1 << (j - 1))][j - 1]);
}
 
int GET_MIN(int l, int r)
{
    int k = __lg(r - l + 1);
    return min(MIN[l][k], MIN[r - (1 << k) + 1][k]);
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
 
    BUILD_ST();
    while (q--)
    {
        int l, r; cin >> l >> r;
        cout << GET_MIN(l, r) << "\n";
    }
 
    return 0;
}