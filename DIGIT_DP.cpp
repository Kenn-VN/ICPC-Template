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

ll n;
ll dp[N][10];

ll DP(int idx, bool tight, int prev, string &num)
{
    if (idx == -1) return 1;
    if (tight == false and dp[idx][prev] >= 0) return dp[idx][prev];

    ll res = 0;
    int k = (tight == true) ? (num[idx] - '0') : 9;
    for (int i = 0; i <= k; i++)
    {
        int new_tight = (num[idx] - '0' == i) ? tight : 0;
        if (prev == 1 and i == 3) continue;
        if (i == 4) continue;
        res += DP(idx - 1, new_tight, i, num);
    }

    if (tight == false) dp[idx][prev] = res;
    return res;
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

    cin >> n;
    string s = to_string(n);
    reverse(s.begin(), s.end());
    memset(dp, -1, sizeof dp);
    cout << n - (DP(s.size() - 1, 1, 0, s) - 1);

    return 0;
}