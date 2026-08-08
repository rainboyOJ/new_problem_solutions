#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500000 + 5;
const int MAXM = 4000000 + 5;

struct Frame {
    int u;          // 当前点
    int in_edge;    // 进入当前点的边编号
    int iter_edge;  // 当前枚举到哪条边
    int child_cnt;  // DFS 树儿子个数
};

int n, m;

// 链式前向星，边编号从 0 开始，方便用 i ^ 1 找反向边。
int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt;

// Tarjan 时间戳。
int dfn[MAXN], low[MAXN], dfs_clock;

// DFS 树父子关系。
int parent_node[MAXN], parent_edge[MAXN];

// 标记割点。
bool is_cut[MAXN];

// 点双使用“点栈”维护当前尚未归属的点。
vector<int> node_stack;

// 当前连通块里访问到的点，用来判断这个连通块里是否存在割点。
vector<int> component_nodes;

// 最终答案。
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
        is_cut[i] = false;
    }
}

void add_edge(int u, int v) {
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
    edge_cnt++;
}

// 处理一个连通块。
// 为了避免 5e5 深度时递归爆栈，这里改成显式栈模拟 DFS。
void solve_component(int root) {
    int answer_before = answer.size();
    component_nodes.clear();

    vector<Frame> call_stack;
    call_stack.push_back({root, -1, head[root], 0});

    parent_node[root] = 0;
    parent_edge[root] = -1;
    dfn[root] = low[root] = ++dfs_clock;
    node_stack.push_back(root);
    component_nodes.push_back(root);

    while (!call_stack.empty()) {
        Frame &cur = call_stack.back();
        int u = cur.u;

        if (cur.iter_edge != -1) {
            int e = cur.iter_edge;
            cur.iter_edge = nxt[e];
            int v = to[e];

            // 只跳过进入当前点那条边的反向边，重边要保留。
            if (e == (cur.in_edge ^ 1)) {
                continue;
            }

            if (!dfn[v]) {
                cur.child_cnt++;
                parent_node[v] = u;
                parent_edge[v] = e;

                call_stack.push_back({v, e, head[v], 0});
                dfn[v] = low[v] = ++dfs_clock;
                node_stack.push_back(v);
                component_nodes.push_back(v);
                continue;
            }

            // 返祖边只能用祖先的 dfn 更新 low。
            if (dfn[v] < dfn[u]) {
                low[u] = min(low[u], dfn[v]);
            }
            continue;
        }

        call_stack.pop_back();

        if (cur.in_edge == -1) {
            // 根节点如果没有 DFS 儿子，说明它是孤立点，
            // 或者只有自环，总之单独构成一个点双。
            if (cur.child_cnt == 0) {
                answer.push_back(vector<int>(1, u));
            }
            else if (cur.child_cnt > 1) {
                is_cut[u] = true;
            }
        }
        else {
            int p = parent_node[u];
            low[p] = min(low[p], low[u]);

            if (low[u] >= dfn[p]) {
                // 非根节点：存在儿子回不到祖先，则它是割点。
                if (parent_edge[p] != -1) {
                    is_cut[p] = true;
                }

                vector<int> bcc;
                while (true) {
                    int x = node_stack.back();
                    node_stack.pop_back();
                    bcc.push_back(x);
                    if (x == u) {
                        break;
                    }
                }
                bcc.push_back(p);
                answer.push_back(bcc);
            }
        }
    }

    // 这个连通块处理结束后，根节点会残留在点栈里，弹掉即可。
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

    // 如果这个连通块本身就没有割点，那么它只会形成一个点双。
    // 做一次升序整理，并把这种“整块就是一个点双”的答案延后输出，
    // 这样可以和题面样例保持同样的展示顺序。
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

    node_stack.reserve(n);
    component_nodes.reserve(n);

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
