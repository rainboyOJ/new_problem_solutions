/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-06-22 19:52
 * update_at: 2026-10-01 22:40
 */
// main.cpp：把规则和询问都转成字符对串，用 AC 自动机匹配，
// 再在 fail 树上按长度阈值离线计数。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// ---- Trie / AC 自动机部分（节点数动态增长，用 vector 存）----

struct TrieEdge {
    int ch;  // 字符对编码 0..675
    int to;  // 子节点
    int nxt; // 同一节点的下一条出边，链式前向星（避开 std::next）
};

struct OutEdge {
    int ch; // 排序后的出边字符对编码
    int to; // 子节点
};

struct TreeEdge {
    int to;  // fail 树上的孩子
    int nxt; // 同一节点的下一条出边
};

// Ask：一个离线子问题
// need：规则长度阈值；state：询问扫描到的 AC 状态；id：原始询问编号
struct Ask {
    int need;
    int state;
    int id;
};

int n, q;

vector<int> trie_head;          // 链式前向星头，-1 表示无出边
vector<int> fail_node;          // fail 指针
vector<int> node_depth;         // 深度 = 该节点对应字符对串的长度
vector<int> out_degree;         // 出边个数，用于给排序边划分区间
vector<ll> terminal_weight;     // 终止节点上挂的规则条数（相同规则不去重）
vector<TrieEdge> trie_edges;    // Trie 出边表

vector<int> edge_start;         // edge_start[u]：节点 u 在 sorted_edges 里的起始下标
vector<OutEdge> sorted_edges;   // 按字符对编码排好序的出边，用于二分查找

vector<int> tree_head;          // fail 树链式前向星头
vector<TreeEdge> tree_edges;    // fail 树出边表
vector<int> tin, tout;          // fail 树 DFS 序，子树对应区间 [tin, tout]
int dfs_timer;

vector<int> terminal_nodes;     // 所有终止节点
vector<Ask> asks;               // 所有离线子问题
vector<ll> answer;              // 每个询问的答案
vector<ll> bit;                 // 树状数组（差分 + 单点查前缀）

// 一对字符 (a, b) 编码成 0..675 的新字符
int code_pair(char a, char b) {
    return (a - 'a') * 26 + (b - 'a');
}

// 新建一个 Trie 节点，返回编号
int new_node() {
    trie_head.push_back(-1);
    fail_node.push_back(0);
    node_depth.push_back(0);
    out_degree.push_back(0);
    terminal_weight.push_back(0);
    int id = trie_head.size() - 1;
    return id;
}

// 在原始出边链表里找 ch 对应的孩子，找不到返回 -1
int find_child_raw(int u, int ch) {
    for (int e = trie_head[u]; e != -1; e = trie_edges[e].nxt) {
        if (trie_edges[e].ch == ch) {
            return trie_edges[e].to;
        }
    }
    return -1;
}

// 给 u 新建一条 ch 出边指向新节点
int add_child(int u, int ch) {
    int v = new_node();
    node_depth[v] = node_depth[u] + 1;

    TrieEdge e;
    e.ch = ch;
    e.to = v;
    e.nxt = trie_head[u];
    trie_head[u] = trie_edges.size();
    trie_edges.push_back(e);
    out_degree[u]++;

    return v;
}

// 取 u 的 ch 孩子，不存在就新建
int get_or_add_child(int u, int ch) {
    int v = find_child_raw(u, ch);
    if (v != -1) {
        return v;
    }
    return add_child(u, ch);
}

// 把规则 (a, b) 的字符对串插入 Trie，终止节点权值 +1
void insert_pair_string(const string &a, const string &b) {
    int u = 0;
    int len = a.size();
    for (int i = 0; i < len; i++) {
        int ch = code_pair(a[i], b[i]);
        u = get_or_add_child(u, ch);
    }
    terminal_weight[u]++;
}

// 按字符对编码排序比较函数
bool cmp_out_edge(const OutEdge &a, const OutEdge &b) {
    return a.ch < b.ch;
}

// 把链式出边整理成每个节点连续一段、段内按字符对升序的 sorted_edges
void build_sorted_edges() {
    int nodes = trie_head.size();
    edge_start.assign(nodes + 1, 0);
    for (int i = 0; i < nodes; i++) {
        edge_start[i + 1] = edge_start[i] + out_degree[i];
    }

    sorted_edges.resize(trie_edges.size());
    vector<int> cur = edge_start;
    for (int u = 0; u < nodes; u++) {
        for (int e = trie_head[u]; e != -1; e = trie_edges[e].nxt) {
            int pos = cur[u]++;
            sorted_edges[pos].ch = trie_edges[e].ch;
            sorted_edges[pos].to = trie_edges[e].to;
        }
    }

    for (int u = 0; u < nodes; u++) {
        int l = edge_start[u];
        int r = edge_start[u + 1];
        if (r - l > 1) {
            sort(sorted_edges.begin() + l, sorted_edges.begin() + r, cmp_out_edge);
        }
    }
}

// 在 u 的排序出边里二分找 ch 孩子，找不到返回 -1
int find_child(int u, int ch) {
    int l = edge_start[u];
    int r = edge_start[u + 1] - 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (sorted_edges[mid].ch == ch) {
            return sorted_edges[mid].to;
        }
        if (sorted_edges[mid].ch < ch) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return -1;
}

// 沿 fail 链走一步转移，返回下一个 AC 状态
int move_state(int u, int ch) {
    while (u != 0 && find_child(u, ch) == -1) {
        u = fail_node[u];
    }
    int v = find_child(u, ch);
    if (v == -1) {
        return 0;
    }
    return v;
}

// BFS 建 AC 自动机的 fail 指针
void build_ac_automaton() {
    build_sorted_edges();

    vector<int> que;
    que.reserve(trie_head.size());

    // 根的孩子 fail 指向根
    for (int e = edge_start[0]; e < edge_start[1]; e++) {
        int v = sorted_edges[e].to;
        fail_node[v] = 0;
        que.push_back(v);
    }

    // que 在循环里会持续增长，size_t 变量动态判长（避免强转）
    for (size_t qi = 0; qi < que.size(); qi++) {
        int u = que[qi];
        for (int e = edge_start[u]; e < edge_start[u + 1]; e++) {
            int ch = sorted_edges[e].ch;
            int v = sorted_edges[e].to;

            int f = fail_node[u];
            while (f != 0 && find_child(f, ch) == -1) {
                f = fail_node[f];
            }
            int go = find_child(f, ch);
            if (go == -1) {
                fail_node[v] = 0;
            } else {
                fail_node[v] = go;
            }
            que.push_back(v);
        }
    }
}

// 给 fail 树加一条 u -> v 的边
void add_tree_edge(int u, int v) {
    TreeEdge e;
    e.to = v;
    e.nxt = tree_head[u];
    tree_head[u] = tree_edges.size();
    tree_edges.push_back(e);
}

// 用 fail 指针建 fail 树，并求 DFS 序（显式栈，防递归爆栈）
void build_fail_tree() {
    int nodes = trie_head.size();
    tree_head.assign(nodes, -1);
    tree_edges.reserve(nodes - 1);

    for (int i = 1; i < nodes; i++) {
        add_tree_edge(fail_node[i], i);
    }

    tin.assign(nodes, 0);
    tout.assign(nodes, 0);
    dfs_timer = 0;

    vector<int> st;
    vector<int> iter;
    st.push_back(0);
    iter.push_back(tree_head[0]);
    tin[0] = ++dfs_timer;

    while (!st.empty()) {
        int u = st.back();
        int &e = iter.back();
        if (e != -1) {
            int v = tree_edges[e].to;
            e = tree_edges[e].nxt;
            tin[v] = ++dfs_timer;
            st.push_back(v);
            iter.push_back(tree_head[v]);
        } else {
            tout[u] = dfs_timer;
            st.pop_back();
            iter.pop_back();
        }
    }
}

// ---- 树状数组：区间加、单点查（差分实现）----

void bit_add(int pos, ll val) {
    int nbit = bit.size() - 1;
    while (pos <= nbit) {
        bit[pos] += val;
        pos += pos & -pos;
    }
}

void bit_range_add(int l, int r, ll val) {
    bit_add(l, val);
    bit_add(r + 1, -val);
}

ll bit_query(int pos) {
    ll res = 0;
    while (pos > 0) {
        res += bit[pos];
        pos -= pos & -pos;
    }
    return res;
}

// 终止节点按深度从大到小排序
bool cmp_terminal_depth(int a, int b) {
    return node_depth[a] > node_depth[b];
}

// 离线子问题按长度阈值从大到小排序
bool cmp_ask_need(const Ask &a, const Ask &b) {
    return a.need > b.need;
}

// 离线回答所有子问题：
// 深度不小于阈值的终止节点，其 fail 子树整体加权后，查状态的 DFS 序位置
void answer_offline_asks() {
    int nodes = trie_head.size();
    bit.assign(nodes + 2, 0);

    sort(terminal_nodes.begin(), terminal_nodes.end(), cmp_terminal_depth);
    sort(asks.begin(), asks.end(), cmp_ask_need);

    int ptr = 0;
    int term_cnt = terminal_nodes.size();
    int ask_cnt = asks.size();
    for (int i = 0; i < ask_cnt; i++) {
        // 把深度足够的终止节点子树加进树状数组
        while (ptr < term_cnt && node_depth[terminal_nodes[ptr]] >= asks[i].need) {
            int u = terminal_nodes[ptr];
            bit_range_add(tin[u], tout[u], terminal_weight[u]);
            ptr++;
        }
        answer[asks[i].id] += bit_query(tin[asks[i].state]);
    }
}

// 处理一个询问：找出 [L,R] 后，把每个可能结束位置拆成一个离线子问题
void process_query(int id, const string &a, const string &b) {
    if (a.size() != b.size()) {
        answer[id] = 0;
        return;
    }

    int len = a.size();
    int first_diff = -1;
    int last_diff = -1;
    for (int i = 0; i < len; i++) {
        if (a[i] != b[i]) {
            if (first_diff == -1) {
                first_diff = i;
            }
            last_diff = i;
        }
    }

    if (first_diff == -1) {
        answer[id] = 0;
        return;
    }

    // 扫描字符对串，每个结束位置 i >= R 产生一个子问题：
    // 统计 fail 祖先中深度 >= i - L + 1 的终止节点数量
    int state = 0;
    for (int i = 0; i < len; i++) {
        int ch = code_pair(a[i], b[i]);
        state = move_state(state, ch);
        if (i >= last_diff) {
            Ask ask;
            ask.need = i - first_diff + 1;
            ask.state = state;
            ask.id = id;
            asks.push_back(ask);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    new_node();

    string a, b;
    for (int i = 1; i <= n; i++) {
        cin >> a >> b;
        insert_pair_string(a, b);
    }

    build_ac_automaton();
    build_fail_tree();

    int nodes = trie_head.size();
    for (int i = 1; i < nodes; i++) {
        if (terminal_weight[i] > 0) {
            terminal_nodes.push_back(i);
        }
    }

    answer.assign(q + 1, 0);
    asks.reserve(1000000);
    for (int id = 1; id <= q; id++) {
        cin >> a >> b;
        process_query(id, a, b);
    }

    answer_offline_asks();

    for (int id = 1; id <= q; id++) {
        cout << answer[id] << '\n';
    }

    return 0;
}
