#include <bits/stdc++.h>
using namespace std;


int z[100005], f[100005];


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    string s; cin >> s;
    int n = s.size();
    s = ' ' + s;
    int j;
    for(int i = 2, L = 0, R = 0; i <= n; i++){
        // Z strike
        if(i <= R) z[i] = min(R - i + 1, z[i - L + 1]);
        while(z[i] + i <= n && (s[z[i] + 1] == s[i + z[i]])) z[i]++;
        if(z[i] + i - 1 > R){
            R = z[i] + i - 1;
            L = i;
        }
        
        // KMP
        j = f[i - 1];
        while(j && s[j + 1] != s[i]) j = f[j];
        if(s[j + 1] == s[i]) f[i] = j + 1;
        else f[i] = 0;
    }

    for(int i = 1; i <= n; i++) cout << z[i] << ' '; cout << '\n';
    for(int i = 1; i <= n; i++) cout << f[i] << ' '; cout << '\n';

    return 0;
}