#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 9;
pair<int, int> a[N] , A , B;
int num[N];
int n;
int calc(pair <int ,int> x , pair<int ,int> y)
{
    return abs(x.first - y.first) + abs(x.second - y.second);
}
signed main()
{
    ios_base::sync_with_stdio(NULL);
    cin.tie(NULL);
    cin >> n;
    for (int i = 1 ; i <= n ; i++)
    num[i] = i  , cin >> a[i].first >> a[i].second;
    cin >> A.first >> A.second;
    cin >> B.first >> B.second;
    int res = 1e18;
    do
    {
      for (int i = 0 ; i <= n ; i++)
      {
        pair <int ,int> place;
        int ans = 0;
        place = A;
        int temp = 0;
        for (int j = 1 ; j <= i ; j++) 
        ans += temp * calc(a[num[j]] , place) , place = a[num[j]] , temp++;
        ans += temp * calc(place , A);
        place = B;
        temp = 0;
        for (int j = n ; j >= i + 1 ; j--)
        ans += temp * calc(a[num[j]] , place) , place = a[num[j]] , temp++;
        ans += temp * calc(place , B);
        res = min(res , ans);
      }
    } while (next_permutation(num + 1 , num + n + 1));
    cout << res;
}