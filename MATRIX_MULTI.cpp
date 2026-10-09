#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;

#define fi first
#define se second

const int inf = 1e9 + 7;
const ll INF = 1e18 + 7;
const int N = 3e5 + 1;
const int MOD = 1e9 + 7;

using mat = array<array<ll, 2>, 2>;

struct MATRIX
{
    mat base = {{{1, 0}, {0, 1}}};

    mat MULTI(mat a, mat b)
    {
        mat res = {{{0, 0}, {0, 0}}};
        for (int i = 0; i < 2; i++) 
            for (int j = 0; j < 2; j++)
                for (int k = 0; k < 2; k++) res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % MOD;
	    return res;
    }

    mat EXP(mat a, ll k)
    {
        if (k == 0) return base;
        mat tmp = EXP(a, k / 2);
        tmp = MULTI(tmp, tmp);
        if (k % 2 == 0) return tmp;
            else return MULTI(tmp, a);
    }

} MATRIX;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    ll n; cin >> n;
    mat F = {{{1, 1}, {1, 0}}};
    F = MATRIX.EXP(F, n);
    cout << F[0][1] << "\n";
    
    return 0;
}