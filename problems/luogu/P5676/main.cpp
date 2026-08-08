#include <bits/stdc++.h>
using namespace std;

struct Frame {
    int u;          // 当前点
    int iter_edge;  // 当前枚举到哪条边
};

int t;
int n;
vector<int> w, e_val;

// 缩点后的“兴奋程度值图”。
vector<int> head, to, nxt;
int edge_cnt;

vector<int> dfn, low, parent_node, scc_id;
vector<int> tarjan_stack;
vector<char> in_stack;
int dfs_clock, scc_cnt;

unordered_map<int, int> value_id;
unordered_map<int, vector<int> > divisor_cache;

void add_edge(int u, int v) {
    to.push_back(v);
    nxt.push_back(head[u]);
    edge_cnt++;
    head[u] = edge_cnt;
}

// 找出 w 的所有“同时也是某个 e 值”的约数，对应的图节点编号。
vector<int> &get_divisor_nodes(int x) {
    unordered_map<int, vector<int> >::iterator it = divisor_cache.find(x);
    if (it != divisor_cache.end()) {
        return it->second;
    }

    vector<int> res;
    for (int d = 1; 1LL * d * d <= x; d++) {
        if (x % d != 0) {
            continue;
        }

        unordered_map<int, int>::iterator it1 = value_id.find(d);
        if (it1 != value_id.end()) {
            res.push_back(it1->second);
        }

        int d2 = x / d;
        if (d2 != d) {
            unordered_map<int, int>::iterator it2 = value_id.find(d2);
            if (it2 != value_id.end()) {
                res.push_back(it2->second);
            }
        }
    }

    divisor_cache[x] = res;
    return divisor_cache[x];
}

// 非递归 Tarjan 求强连通分量，避免值图退化成长链时爆栈。
void tarjan_scc(int start) {
    vector<Frame> call_stack;

    call_stack.push_back({start, head[start]});
    parent_node[start] = 0;
    dfn[start] = low[start] = ++dfs_clock;
    tarjan_stack.push_back(start);
    in_stack[start] = 1;

    while (!call_stack.empty()) {
        Frame &cur = call_stack.back();
        int u = cur.u;

        if (cur.iter_edge != 0) {
            int e = cur.iter_edge;
            cur.iter_edge = nxt[e];
            int v = to[e];

            if (!dfn[v]) {
                parent_node[v] = u;
                dfn[v] = low[v] = ++dfs_clock;
                tarjan_stack.push_back(v);
                in_stack[v] = 1;
                call_stack.push_back({v, head[v]});
                continue;
            }

            if (in_stack[v]) {
                low[u] = min(low[u], dfn[v]);
            }
            continue;
        }

        call_stack.pop_back();

        if (parent_node[u] != 0) {
            int p = parent_node[u];
            low[p] = min(low[p], low[u]);
        }

        if (low[u] == dfn[u]) {
            scc_cnt++;
            while (true) {
                int x = tarjan_stack.back();
                tarjan_stack.pop_back();
                in_stack[x] = 0;
                scc_id[x] = scc_cnt;
                if (x == u) {
                    break;
                }
            }
        }
    }
}

int solve_case() {
    cin >> n;

    w.assign(n + 1, 0);
    e_val.assign(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> e_val[i];
    }

    vector<int> values;
    values.reserve(n);
    for (int i = 1; i <= n; i++) {
        values.push_back(e_val[i]);
    }
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());

    int value_cnt = values.size();

    value_id.clear();
    value_id.reserve(value_cnt * 2 + 5);
    for (int i = 0; i < value_cnt; i++) {
        value_id[values[i]] = i + 1;
    }

    divisor_cache.clear();
    divisor_cache.reserve(n * 2 + 5);

    head.assign(value_cnt + 1, 0);
    to.assign(1, 0);
    nxt.assign(1, 0);
    edge_cnt = 0;

    // 建值图：x -> e_i，表示当前兴奋值是 x 时，可以选择第 i 个游戏。
    for (int i = 1; i <= n; i++) {
        int target = value_id[e_val[i]];
        vector<int> &div_nodes = get_divisor_nodes(w[i]);
        for (size_t j = 0; j < div_nodes.size(); j++) {
            add_edge(div_nodes[j], target);
        }
    }

    dfn.assign(value_cnt + 1, 0);
    low.assign(value_cnt + 1, 0);
    parent_node.assign(value_cnt + 1, 0);
    scc_id.assign(value_cnt + 1, 0);
    in_stack.assign(value_cnt + 1, 0);
    tarjan_stack.clear();
    tarjan_stack.reserve(value_cnt);
    dfs_clock = 0;
    scc_cnt = 0;

    for (int i = 1; i <= value_cnt; i++) {
        if (!dfn[i]) {
            tarjan_scc(i);
        }
    }

    int answer = 0;

    // 游戏 i 能玩两次：
    // e_i 可以走到某个 x，并且 x 能再次选择 i。
    // 后者等价于 x | w_i，所以只要找到一个与 e_i 同 SCC 的约数值 x 即可。
    for (int i = 1; i <= n; i++) {
        int my_scc = scc_id[value_id[e_val[i]]];
        vector<int> &div_nodes = get_divisor_nodes(w[i]);

        bool ok = false;
        for (size_t j = 0; j < div_nodes.size(); j++) {
            if (scc_id[div_nodes[j]] == my_scc) {
                ok = true;
                break;
            }
        }

        if (ok) {
            answer++;
        }
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t;
    while (t--) {
        cout << solve_case() << '\n';
    }

    return 0;
}
