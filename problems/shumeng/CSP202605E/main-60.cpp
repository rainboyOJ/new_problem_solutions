/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-08-17 23:41
 */
// 60 分做法：枚举第一次聚拢中心，对每个中心贪心求最小串。
// 时间复杂度 O(n^2 log n)，适用于 n <= 3000。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int INF = 1000000000;

int n;
vector<int> graph[MAXN]; // 树的邻接表，按点编号升序排列

int root_vertex;
int parent_vertex[MAXN]; // 以 root_vertex 为根时的父亲
int bfs_order[MAXN];

int minimum_child[MAXN]; // 不经过父亲能加入的最小字符
int red_parent[MAXN];    // 根路径上最近的红色祖先
int value_head[MAXN];    // 按 minimum_child 对红点分类
int value_next[MAXN];

int red_head[MAXN];      // 红点压缩树的邻接表
int red_tail[MAXN];
vector<int> red_to;
vector<int> red_next;

bool active[MAXN];       // 该点还可以成为下一次聚拢中心
bool in_frontier[MAXN];  // 该点与已处理部分相邻
bool is_red[MAXN];       // minimum_child 比当前串首更小

// frontier 中存 (minimum_child, 点)，visible_red 中存没有红色祖先的红点。
set<pair<int, int> > frontier;
set<pair<int, int> > visible_red;

vector<int> root_piece;
vector<int> answer_buffer;
int answer_left, answer_right;
int current_head;

int child_count(int u) {
    return (int)graph[u].size() - (u != root_vertex);
}

int find_minimum_child(int u) {
    for (int i = 0; i < (int)graph[u].size(); i++) {
        int v = graph[u][i];
        if (v != parent_vertex[u]) {
            return v;
        }
    }
    return INF;
}

void add_red_edge(int father, int son) {
    int edge = (int)red_to.size();
    red_to.push_back(son);
    red_next.push_back(-1);

    if (red_head[father] == -1) {
        red_head[father] = red_tail[father] = edge;
    } else {
        red_next[red_tail[father]] = edge;
        red_tail[father] = edge;
    }
}

// 删除红点 x，并把它仍然有效的红色儿子接到 x 的红色父亲下面。
void erase_red(int x) {
    if (!is_red[x]) {
        return;
    }
    is_red[x] = false;

    int father = red_parent[x];
    if (father == -1) {
        visible_red.erase(make_pair(minimum_child[x], x));
    }

    for (int edge = red_head[x]; edge != -1; edge = red_next[edge]) {
        int y = red_to[edge];
        if (!is_red[y] || red_parent[y] != x) {
            continue;
        }
        red_parent[y] = father;
        if (father == -1) {
            visible_red.insert(make_pair(minimum_child[y], y));
        } else {
            add_red_edge(father, y);
        }
    }
}

// 找到 u 的儿子中第一个不小于 value 的点。
int next_child(int u, int value) {
    vector<int>::iterator it = lower_bound(graph[u].begin(), graph[u].end(), value);
    while (it != graph[u].end() && *it == parent_vertex[u]) {
        ++it;
    }
    return it == graph[u].end() ? -1 : *it;
}

void build_rooted_tree(int root) {
    fill(parent_vertex, parent_vertex + n, -1);
    int order_size = 1;
    bfs_order[0] = root;

    for (int i = 0; i < order_size; i++) {
        int u = bfs_order[i];
        for (int j = 0; j < (int)graph[u].size(); j++) {
            int v = graph[u][j];
            if (v == parent_vertex[u]) {
                continue;
            }
            parent_vertex[v] = u;
            bfs_order[order_size++] = v;
        }
    }
}

// 第一次在 root 聚拢时，root 及所有邻点可以直接按编号升序拼接。
void build_first_string(int root) {
    root_piece.clear();
    bool inserted = false;
    for (int i = 0; i < (int)graph[root].size(); i++) {
        int v = graph[root][i];
        if (!inserted && root < v) {
            root_piece.push_back(root);
            inserted = true;
        }
        root_piece.push_back(v);
    }
    if (!inserted) {
        root_piece.push_back(root);
    }

    answer_buffer.assign(2 * n + 5, 0);
    answer_left = answer_right = n;
    for (int i = 0; i < (int)root_piece.size(); i++) {
        answer_buffer[answer_right++] = root_piece[i];
    }
    current_head = answer_buffer[answer_left];
}

void prepare(int root) {
    root_vertex = root;
    build_rooted_tree(root);
    build_first_string(root);

    fill(minimum_child, minimum_child + n, INF);
    fill(red_parent, red_parent + n, -2);
    fill(value_head, value_head + n, -1);
    fill(value_next, value_next + n, -1);
    fill(red_head, red_head + n, -1);
    fill(red_tail, red_tail + n, -1);
    fill(active, active + n, false);
    fill(in_frontier, in_frontier + n, false);
    fill(is_red, is_red + n, false);

    red_to.clear();
    red_next.clear();
    frontier.clear();
    visible_red.clear();

    for (int u = 0; u < n; u++) {
        if (u == root || child_count(u) == 0) {
            continue;
        }
        active[u] = true;
        minimum_child[u] = find_minimum_child(u);
        if (minimum_child[u] < current_head) {
            is_red[u] = true;
            value_next[u] = value_head[minimum_child[u]];
            value_head[minimum_child[u]] = u;
        }
    }

    for (int i = 0; i < (int)graph[root].size(); i++) {
        int v = graph[root][i];
        if (active[v]) {
            in_frontier[v] = true;
            frontier.insert(make_pair(minimum_child[v], v));
        }
    }

    // 用栈建立红点压缩树，last_red 是根路径上最近的红点。
    vector<pair<int, int> > stack;
    stack.push_back(make_pair(root, -1));
    while (!stack.empty()) {
        int u = stack.back().first;
        int last_red = stack.back().second;
        stack.pop_back();

        for (int i = (int)graph[u].size() - 1; i >= 0; i--) {
            int v = graph[u][i];
            if (v == parent_vertex[u]) {
                continue;
            }
            if (is_red[v]) {
                red_parent[v] = last_red;
                if (last_red == -1) {
                    visible_red.insert(make_pair(minimum_child[v], v));
                } else {
                    add_red_edge(last_red, v);
                }
                stack.push_back(make_pair(v, v));
            } else {
                stack.push_back(make_pair(v, last_red));
            }
        }
    }
}

// 选择下一个聚拢中心后，把它的所有儿子按字典序最优的位置接入当前串。
void append_children(int u) {
    int old_head = current_head;
    int cut = (int)(lower_bound(graph[u].begin(), graph[u].end(), old_head) -
                    graph[u].begin());

    for (int i = cut - 1; i >= 0; i--) {
        if (graph[u][i] != parent_vertex[u]) {
            answer_buffer[--answer_left] = graph[u][i];
        }
    }
    for (int i = cut; i < (int)graph[u].size(); i++) {
        if (graph[u][i] != parent_vertex[u]) {
            answer_buffer[answer_right++] = graph[u][i];
        }
    }

    active[u] = false;
    for (int i = 0; i < (int)graph[u].size(); i++) {
        int v = graph[u][i];
        if (v != parent_vertex[u] && active[v]) {
            in_frontier[v] = true;
            frontier.insert(make_pair(minimum_child[v], v));
        }
    }

    int new_head = answer_buffer[answer_left];
    if (new_head < old_head) {
        for (int value = old_head - 1; value >= new_head; value--) {
            for (int x = value_head[value]; x != -1; x = value_next[x]) {
                erase_red(x);
            }
        }
        current_head = new_head;
    }
}

// 固定第一次聚拢中心 root，按字典序贪心生成这个起点对应的最小答案。
vector<int> solve_root(int root) {
    prepare(root);

    while (answer_right - answer_left < n) {
        int bad = -1;
        int value_after_bad = -1;
        if (!visible_red.empty()) {
            bad = visible_red.rbegin()->second;
            value_after_bad = next_child(bad, current_head);
        }

        int first_frontier = -1;
        set<pair<int, int> >::iterator it =
            frontier.upper_bound(make_pair(current_head, INF));
        if (it != frontier.end()) {
            first_frontier = it->second;
        }

        int chosen;
        if (first_frontier != -1 &&
            (bad == -1 || !in_frontier[bad] ||
             (value_after_bad != -1 &&
              minimum_child[first_frontier] < value_after_bad))) {
            chosen = first_frontier;
        } else {
            chosen = bad;
        }

        // 合法状态下一定存在可扩展点；保留保护分支，避免异常输入导致越界。
        if (chosen == -1) {
            return vector<int>(n, INF);
        }

        if (in_frontier[chosen]) {
            frontier.erase(make_pair(minimum_child[chosen], chosen));
            in_frontier[chosen] = false;
        }
        erase_red(chosen);
        append_children(chosen);
    }

    return vector<int>(answer_buffer.begin() + answer_left,
                       answer_buffer.begin() + answer_right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    for (int u = 0; u < n; u++) {
        sort(graph[u].begin(), graph[u].end());
    }

    vector<int> answer(n, INF);
    for (int root = 0; root < n; root++) {
        vector<int> current = solve_root(root);
        if (current < answer) {
            answer = current;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << answer[i] + 1 << " \n"[i == n - 1];
    }
    return 0;
}
