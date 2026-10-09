#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 1;

int n, m;
vector<int> adj[N], dag_adj[N];

int num[N], low[N], scc_id[N];
int in_deg[N], out_deg[N];
bool on_stack[N];

vector<int> rep;
stack<int> st;

int timer = 0, scc_count = 0;

void tarjan(int u) {
    num[u] = low[u] = ++timer;
    st.push(u);
    on_stack[u] = true;

    for (int v : adj[u]) {
        if (!num[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (on_stack[v]) {
            low[u] = min(low[u], num[v]);
        }
    }

    if (low[u] == num[u]) {
        ++scc_count;
        rep.push_back(u);

        while (true) {
            int v = st.top();
            st.pop();

            on_stack[v] = false;
            scc_id[v] = scc_count;

            if (u == v) break;
        }
    }
}

void build_DAG() {
    set<pair<int, int>> edges;

    for (int u = 1; u <= n; ++u) {
        for (int v : adj[u]) {
            int cu = scc_id[u];
            int cv = scc_id[v];

            if (cu != cv && edges.insert({cu, cv}).second) {
                dag_adj[cu].push_back(cv);
                ++out_deg[cu];
                ++in_deg[cv];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    rep.push_back(0);  // Để rep được đánh số từ 1.

    for (int u = 1; u <= n; ++u) {
        if (!num[u]) tarjan(u);
    }

    build_DAG();

    // scc_count: số đỉnh của DAG.
    // scc_id[u]: SCC chứa đỉnh gốc u.
    // rep[c]: một đỉnh gốc đại diện cho SCC c.
    // dag_adj[c]: các SCC có cạnh đi từ c tới.
    // in_deg[c], out_deg[c]: bậc vào / ra của SCC c.
}