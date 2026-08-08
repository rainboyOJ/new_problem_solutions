#include <bits/stdc++.h>
using namespace std;

struct TrieEdge {
    int ch;
    int to;
    int next;
};

struct OutEdge {
    int ch;
    int to;
};

struct TreeEdge {
    int to;
    int next;
};

struct Ask {
    int need;
    int state;
    int id;
};

int n, q;

vector<int> trie_head;
vector<int> fail_node;
vector<int> node_depth;
vector<int> out_degree;
vector<long long> terminal_weight;
vector<TrieEdge> trie_edges;

vector<int> edge_start;
vector<OutEdge> sorted_edges;

vector<int> tree_head;
vector<TreeEdge> tree_edges;
vector<int> tin, tout;
int dfs_timer;

vector<int> terminal_nodes;
vector<Ask> asks;
vector<long long> answer;
vector<long long> bit;

int code_pair(char a, char b) {
    return (a - 'a') * 26 + (b - 'a');
}

int new_node() {
    trie_head.push_back(-1);
    fail_node.push_back(0);
    node_depth.push_back(0);
    out_degree.push_back(0);
    terminal_weight.push_back(0);
    return (int)trie_head.size() - 1;
}

int find_child_raw(int u, int ch) {
    for (int e = trie_head[u]; e != -1; e = trie_edges[e].next) {
        if (trie_edges[e].ch == ch) {
            return trie_edges[e].to;
        }
    }
    return -1;
}

int add_child(int u, int ch) {
    int v = new_node();
    node_depth[v] = node_depth[u] + 1;

    TrieEdge e;
    e.ch = ch;
    e.to = v;
    e.next = trie_head[u];
    trie_head[u] = (int)trie_edges.size();
    trie_edges.push_back(e);
    out_degree[u]++;

    return v;
}

int get_or_add_child(int u, int ch) {
    int v = find_child_raw(u, ch);
    if (v != -1) {
        return v;
    }
    return add_child(u, ch);
}

void insert_pair_string(const string &a, const string &b) {
    int u = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        int ch = code_pair(a[i], b[i]);
        u = get_or_add_child(u, ch);
    }
    terminal_weight[u]++;
}

bool cmp_out_edge(const OutEdge &a, const OutEdge &b) {
    return a.ch < b.ch;
}

void build_sorted_edges() {
    int nodes = (int)trie_head.size();
    edge_start.assign(nodes + 1, 0);
    for (int i = 0; i < nodes; i++) {
        edge_start[i + 1] = edge_start[i] + out_degree[i];
    }

    sorted_edges.resize(trie_edges.size());
    vector<int> cur = edge_start;
    for (int u = 0; u < nodes; u++) {
        for (int e = trie_head[u]; e != -1; e = trie_edges[e].next) {
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

void build_ac_automaton() {
    build_sorted_edges();

    vector<int> que;
    que.reserve(trie_head.size());

    for (int e = edge_start[0]; e < edge_start[1]; e++) {
        int v = sorted_edges[e].to;
        fail_node[v] = 0;
        que.push_back(v);
    }

    for (int head = 0; head < (int)que.size(); head++) {
        int u = que[head];
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

void add_tree_edge(int u, int v) {
    TreeEdge e;
    e.to = v;
    e.next = tree_head[u];
    tree_head[u] = (int)tree_edges.size();
    tree_edges.push_back(e);
}

void build_fail_tree() {
    int nodes = (int)trie_head.size();
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
            e = tree_edges[e].next;
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

void bit_add(int pos, long long val) {
    int nbit = (int)bit.size() - 1;
    while (pos <= nbit) {
        bit[pos] += val;
        pos += pos & -pos;
    }
}

void bit_range_add(int l, int r, long long val) {
    bit_add(l, val);
    bit_add(r + 1, -val);
}

long long bit_query(int pos) {
    long long res = 0;
    while (pos > 0) {
        res += bit[pos];
        pos -= pos & -pos;
    }
    return res;
}

bool cmp_terminal_depth(int a, int b) {
    return node_depth[a] > node_depth[b];
}

bool cmp_ask_need(const Ask &a, const Ask &b) {
    return a.need > b.need;
}

void answer_offline_asks() {
    int nodes = (int)trie_head.size();
    bit.assign(nodes + 2, 0);

    sort(terminal_nodes.begin(), terminal_nodes.end(), cmp_terminal_depth);
    sort(asks.begin(), asks.end(), cmp_ask_need);

    int ptr = 0;
    for (int i = 0; i < (int)asks.size(); i++) {
        while (ptr < (int)terminal_nodes.size() && node_depth[terminal_nodes[ptr]] >= asks[i].need) {
            int u = terminal_nodes[ptr];
            bit_range_add(tin[u], tout[u], terminal_weight[u]);
            ptr++;
        }
        answer[asks[i].id] += bit_query(tin[asks[i].state]);
    }
}

void process_query(int id, const string &a, const string &b) {
    if (a.size() != b.size()) {
        answer[id] = 0;
        return;
    }

    int len = (int)a.size();
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

    int nodes = (int)trie_head.size();
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
