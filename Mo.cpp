#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30000 + 5;
const int MAXA = 1000000 + 5;

int a[MAXN], cnt[MAXA];
int distinct = 0;

struct Query {
    int l, r, id, block;
};

void add(int pos) {
    int x = a[pos];
    if (cnt[x] == 0) distinct++;
    cnt[x]++;
}

void remove(int pos) {
    int x = a[pos];
    cnt[x]--;
    if (cnt[x] == 0) distinct--;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    int q;
    cin >> q;

    int B = max(1, (int)sqrt(n));
    vector<Query> queries(q);
    vector<int> ans(q);

    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
        queries[i].block = (queries[i].l - 1) / B;
    }

    sort(queries.begin(), queries.end(),
         [](const Query &u, const Query &v) {
             if (u.block != v.block)
                 return u.block < v.block;

             if (u.block % 2 == 0)
                 return u.r < v.r;

             return u.r > v.r;
         });

    int L = 1, R = 0;

    for (const Query &query : queries) {
        int l = query.l;
        int r = query.r;

        while (L > l) add(--L);
        while (R < r) add(++R);
        while (L < l) remove(L++);
        while (R > r) remove(R--);

        ans[query.id] = distinct;
    }

    for (int x : ans)
        cout << x << '\n';

    return 0;
}