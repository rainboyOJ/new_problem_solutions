// brute.cpp：更直观的递归 Tarjan 教学版。
// 它和正式做法的判定逻辑一样，但递归深度只适合小数据，
// 主要用来帮助理解点栈出栈过程，并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;
const int MAXM = 100;

int n, m;
int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt;

int dfn[MAXN], low[MAXN], dfs_clock;
int parent_edge[MAXN];
bool is_cut[MAXN];

vector<int> node_stack;
vector<int> component_nodes;
vector< vector<int> > answer;
vector< vector<int> > deferred_answer;

void init_graph() {
    edge_cnt = 0;
    dfs_clock = 0;
    answer.clear();
    deferred_answer.clear();
    node_stack.clear();

    for (int i = 1; i <= n; i++) {
        head[i] = -1;
        dfn[i] = 0;
        low[i] = 0;
        parent_edge[i] = -1;
        is_cut[i] = false;
    }
}

void add_edge(int u, int v) {
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
    edge_cnt++;
}

void dfs(int u, int in_edge, int root) {
    dfn[u] = low[u] = ++dfs_clock;
    node_stack.push_back(u);
    component_nodes.push_back(u);

    int child_cnt = 0;

    for (int i = head[u]; i != -1; i = nxt[i]) {
        int v = to[i];

        if (i == (in_edge ^ 1)) {
            continue;
        }

        if (!dfn[v]) {
            child_cnt++;
            parent_edge[v] = i;
            dfs(v, i, root);

            low[u] = min(low[u], low[v]);

            if (low[v] >= dfn[u]) {
                if (u != root) {
                    is_cut[u] = true;
                }

                vector<int> bcc;
                while (true) {
                    int x = node_stack.back();
                    node_stack.pop_back();
                    bcc.push_back(x);
                    if (x == v) {
                        break;
                    }
                }
                bcc.push_back(u);
                answer.push_back(bcc);
            }
        }
        else if (dfn[v] < dfn[u]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (u == root) {
        if (child_cnt == 0) {
            answer.push_back(vector<int>(1, u));
        }
        else if (child_cnt > 1) {
            is_cut[u] = true;
        }
    }
}

void solve_component(int root) {
    int answer_before = answer.size();
    component_nodes.clear();

    dfs(root, -1, root);

    if (!node_stack.empty() && node_stack.back() == root) {
        node_stack.pop_back();
    }

    bool has_cut = false;
    for (size_t i = 0; i < component_nodes.size(); i++) {
        if (is_cut[component_nodes[i]]) {
            has_cut = true;
            break;
        }
    }

    int new_bcc_cnt = (int)answer.size() - answer_before;
    if (new_bcc_cnt == 1 && !has_cut) {
        sort(answer[answer_before].begin(), answer[answer_before].end());
        if ((int)answer[answer_before].size() > 1) {
            deferred_answer.push_back(answer[answer_before]);
            answer.pop_back();
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    init_graph();

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            solve_component(i);
        }
    }

    for (size_t i = 0; i < deferred_answer.size(); i++) {
        answer.push_back(deferred_answer[i]);
    }

    cout << answer.size() << '\n';
    for (size_t i = 0; i < answer.size(); i++) {
        cout << answer[i].size();
        for (size_t j = 0; j < answer[i].size(); j++) {
            cout << ' ' << answer[i][j];
        }
        cout << '\n';
    }

    return 0;
}
