//Given 2 strings S and T, count the number of occurrences of T in S (how many substring of S = T)

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
const int N = 1e6 + 5;
const int MOD = 1e9 + 7;
const int base = 31;

string S, C;
int n, m;
ll h[N], POW[N];

ll GET_HASH(int l, int r)
{
    return ((h[r] - h[l - 1] * POW[r - l + 1]) % MOD + MOD) % MOD;
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

    cin >> S >> C;

    int n = S.size();
    int m = C.size();

    S = " " + S;
    C = " " + C;

    POW[0] = 1;
    for (int i = 1; i <= n; i++) POW[i] = POW[i - 1] * base % MOD;

    for (int i = 1; i <= n; i++) h[i] = (h[i - 1] * base + (S[i] - 'a' + 1)) % MOD;

    ll hashC = 0;
    for (int i = 1; i <= m; i++) hashC = (hashC * base + (C[i] - 'a' + 1)) % MOD;

    int res = 0;
    for (int i = m; i <= n; i++)
        if (hashC == GET_HASH(i - m + 1, i)) res++;

    cout << res << "\n";

    return 0;
}