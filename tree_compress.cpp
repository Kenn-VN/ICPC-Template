#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
const int M = 200005;

int n, m;

// adj[u] chứa {đỉnh kề, id cạnh}.
vector<pair<int, int>> adj[N];
vector<pair<int, int>> edges;
vector<int> tree_adj[N];

int num[N], low[N], comp[N];
bool is_bridge[M];

int timer = 0, comp_count = 0;

// 1. Tìm cầu.
void find_bridges(int u, int parent_edge = -1) {
    num[u] = low[u] = ++timer;

    for (auto [v, id] : adj[u]) {
        if (id == parent_edge) continue;

        if (!num[v]) {
            find_bridges(v, id);
            low[u] = min(low[u], low[v]);

            if (low[v] > num[u]) {
                is_bridge[id] = true;
            }
        } else {
            low[u] = min(low[u], num[v]);
        }
    }
}

// 2. Gom thành phần liên thông khi bỏ các cầu.
void assign_component(int u) {
    comp[u] = comp_count;

    for (auto [v, id] : adj[u]) {
        if (is_bridge[id] || comp[v]) continue;
        assign_component(v);
    }
}

void build_tree() {
    for (int u = 1; u <= n; ++u) {
        if (!num[u]) find_bridges(u);
    }

    for (int u = 1; u <= n; ++u) {
        if (!comp[u]) {
            ++comp_count;
            assign_component(u);
        }
    }

    // 3. Mỗi cầu nối hai thành phần khác nhau.
    for (int id = 0; id < m; ++id) {
        if (!is_bridge[id]) continue;

        auto [u, v] = edges[id];
        int cu = comp[u], cv = comp[v];

        tree_adj[cu].push_back(cv);
        tree_adj[cv].push_back(cu);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int id = 0; id < m; ++id) {
        int u, v;
        cin >> u >> v;

        edges.push_back({u, v});
        adj[u].push_back({v, id});
        adj[v].push_back({u, id});
    }

    build_tree();

    // comp[u]: đỉnh chứa u trong cây nén.
    // comp_count: số đỉnh của cây nén.
    // tree_adj[c]: các đỉnh kề với c trong cây nén.
}