/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 10:45
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000;
const int MAXM = 200000;
const int MAXV = MAXN + MAXM + 5;
const int LOG = 20;

struct Edge {
    int to;
    int id;
};

int n, m, q;
vector<Edge> graph[MAXN + 1];
int edge_u[MAXM + 1];
int edge_v[MAXM + 1];
int discovery[MAXN + 1];
int low[MAXN + 1];
int dfs_clock;
vector<int> edge_stack;

vector<int> block_tree[MAXV];
int total_nodes;
int component_seen[MAXN + 1];
int component_id;
bool is_articulation[MAXV];

int tree_parent[MAXV];
int tree_depth[MAXV];
int tree_tin[MAXV];
int tree_tout[MAXV];
int tree_timer;
int up[LOG][MAXV];
int articulation_prefix[MAXV];

int mark_stamp[MAXV];
int virtual_index[MAXV];

void add_block() {
    component_id++;
    vector<int> vertices;
    while (true) {
        int edge_id = edge_stack.back();
        edge_stack.pop_back();
        int x = edge_u[edge_id];
        int y = edge_v[edge_id];
        if (component_seen[x] != component_id) {
            component_seen[x] = component_id;
            vertices.push_back(x);
        }
        if (component_seen[y] != component_id) {
            component_seen[y] = component_id;
            vertices.push_back(y);
        }
        if (edge_id == -1) {
            break;
        }
    }
    // The marker -1 is not used; this branch is kept unreachable.
}

void make_block_until(int stop_edge) {
    component_id++;
    vector<int> vertices;
    while (true) {
        int edge_id = edge_stack.back();
        edge_stack.pop_back();
        int x = edge_u[edge_id];
        int y = edge_v[edge_id];
        if (component_seen[x] != component_id) {
            component_seen[x] = component_id;
            vertices.push_back(x);
        }
        if (component_seen[y] != component_id) {
            component_seen[y] = component_id;
            vertices.push_back(y);
        }
        if (edge_id == stop_edge) {
            break;
        }
    }
    total_nodes++;
    int block = total_nodes;
    for (int i = 0; i < (int)vertices.size(); i++) {
        block_tree[block].push_back(vertices[i]);
        block_tree[vertices[i]].push_back(block);
    }
}

void tarjan(int u, int parent_edge) {
    discovery[u] = low[u] = ++dfs_clock;
    for (int i = 0; i < (int)graph[u].size(); i++) {
        int v = graph[u][i].to;
        int edge_id = graph[u][i].id;
        if (edge_id == parent_edge) {
            continue;
        }
        if (discovery[v] == 0) {
            edge_stack.push_back(edge_id);
            tarjan(v, edge_id);
            low[u] = min(low[u], low[v]);
            if (low[v] >= discovery[u]) {
                make_block_until(edge_id);
            }
        } else if (discovery[v] < discovery[u]) {
            edge_stack.push_back(edge_id);
            low[u] = min(low[u], discovery[v]);
        }
    }
}

void build_tree_info() {
    vector<int> iterator_index(total_nodes + 1, 0);
    vector<int> stack_nodes;
    stack_nodes.push_back(1);
    tree_parent[1] = 0;
    tree_depth[1] = 0;
    while (!stack_nodes.empty()) {
        int u = stack_nodes.back();
        if (tree_tin[u] == 0) {
            tree_tin[u] = ++tree_timer;
            articulation_prefix[u] = (u <= n && is_articulation[u]) ? 1 : 0;
            if (tree_parent[u] != 0) {
                articulation_prefix[u] += articulation_prefix[tree_parent[u]];
            }
        }
        if (iterator_index[u] == (int)block_tree[u].size()) {
            tree_tout[u] = tree_timer;
            stack_nodes.pop_back();
            continue;
        }
        int v = block_tree[u][iterator_index[u]++];
        if (v == tree_parent[u]) {
            continue;
        }
        tree_parent[v] = u;
        tree_depth[v] = tree_depth[u] + 1;
        stack_nodes.push_back(v);
    }

    for (int u = 1; u <= total_nodes; u++) {
        up[0][u] = tree_parent[u];
    }
    for (int j = 1; j < LOG; j++) {
        for (int u = 1; u <= total_nodes; u++) {
            up[j][u] = up[j - 1][up[j - 1][u]];
        }
    }
}

bool is_ancestor(int u, int v) {
    return tree_tin[u] <= tree_tin[v] && tree_tout[v] <= tree_tout[u];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) {
        return u;
    }
    if (is_ancestor(v, u)) {
        return v;
    }
    int x = u;
    for (int j = LOG - 1; j >= 0; j--) {
        if (up[j][x] != 0 && !is_ancestor(up[j][x], v)) {
            x = up[j][x];
        }
    }
    return tree_parent[x];
}

int marked_value(int u, int query_id) {
    return mark_stamp[u] == query_id ? 1 : 0;
}

long long solve_query(const vector<int> &marked, int query_id) {
    int count_marked = (int)marked.size();
    vector<int> nodes = marked;
    sort(nodes.begin(), nodes.end(), [](int x, int y) {
        return tree_tin[x] < tree_tin[y];
    });
    int original_size = (int)nodes.size();
    for (int i = 1; i < original_size; i++) {
        nodes.push_back(lca(nodes[i - 1], nodes[i]));
    }
    sort(nodes.begin(), nodes.end(), [](int x, int y) {
        return tree_tin[x] < tree_tin[y];
    });
    nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());

    int size = (int)nodes.size();
    for (int i = 0; i < size; i++) {
        virtual_index[nodes[i]] = i;
    }
    vector<int> parent_index(size, -1);
    vector<int> stack_nodes;
    for (int i = 0; i < size; i++) {
        while (!stack_nodes.empty() && !is_ancestor(stack_nodes.back(), nodes[i])) {
            stack_nodes.pop_back();
        }
        if (!stack_nodes.empty()) {
            parent_index[i] = virtual_index[stack_nodes.back()];
        }
        stack_nodes.push_back(nodes[i]);
    }

    vector<int> subtree_count(size, 0);
    for (int i = 0; i < size; i++) {
        subtree_count[i] = marked_value(nodes[i], query_id);
    }
    for (int i = size - 1; i > 0; i--) {
        subtree_count[parent_index[i]] += subtree_count[i];
    }

    vector<int> maximum_child(size, 0);
    for (int i = 1; i < size; i++) {
        int p = parent_index[i];
        maximum_child[p] = max(maximum_child[p], subtree_count[i]);
    }

    long long answer = 1LL * (n - 1) * count_marked;
    for (int i = 0; i < size; i++) {
        int u = nodes[i];
        if (u <= n && is_articulation[u]) {
            int best = max(maximum_child[i], count_marked - subtree_count[i]);
            int normal = count_marked - marked_value(u, query_id);
            answer += best - normal;
        }
    }

    for (int i = 1; i < size; i++) {
        int child = nodes[i];
        int parent = nodes[parent_index[i]];
        int between = articulation_prefix[child] - articulation_prefix[parent]
                      - ((child <= n && is_articulation[child]) ? 1 : 0);
        if (between == 0) {
            continue;
        }
        int branch = subtree_count[i];
        int best = max(branch, count_marked - branch);
        answer += 1LL * between * (best - count_marked);
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q;
    for (int i = 1; i <= m; i++) {
        cin >> edge_u[i] >> edge_v[i];
        graph[edge_u[i]].push_back({edge_v[i], i});
        graph[edge_v[i]].push_back({edge_u[i], i});
    }
    total_nodes = n;
    tarjan(1, 0);
    for (int u = 1; u <= n; u++) {
        is_articulation[u] = block_tree[u].size() > 1;
    }
    build_tree_info();

    for (int query_id = 1; query_id <= q; query_id++) {
        int c;
        cin >> c;
        vector<int> marked(c);
        for (int i = 0; i < c; i++) {
            cin >> marked[i];
            mark_stamp[marked[i]] = query_id;
        }
        cout << solve_query(marked, query_id) << '\n';
    }
    return 0;
}
