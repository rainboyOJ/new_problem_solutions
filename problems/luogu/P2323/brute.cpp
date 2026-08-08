// brute.cpp：小数据枚举所有生成树，再枚举一级/二级公路分配。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;
const int MAXM = 20;
const int INF = 1e9;

struct Edge {
    int id;
    int u, v;
    int c1, c2;
} edges[MAXM];

struct AnswerEdge {
    int id;
    int level;
};

int n, need_level1, m_input;
int edge_cnt;
int picked[MAXM];
int fa[MAXN];
int best_cost = INF;
vector<AnswerEdge> best_answer;

void init_dsu() {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
}

int find_root(int x) {
    if (fa[x] == x) {
        return x;
    }
    fa[x] = find_root(fa[x]);
    return fa[x];
}

bool unite(int x, int y) {
    x = find_root(x);
    y = find_root(y);
    if (x == y) {
        return false;
    }
    fa[x] = y;
    return true;
}

void update_answer(const vector<AnswerEdge> &answer, int cost) {
    vector<AnswerEdge> cur = answer;
    sort(cur.begin(), cur.end(), [](const AnswerEdge &a, const AnswerEdge &b) {
        return a.id < b.id;
    });

    if (cost < best_cost) {
        best_cost = cost;
        best_answer = cur;
    }
}

void enumerate_types(int pos, int cnt_level1, int cur_cost, vector<AnswerEdge> &answer) {
    if (pos > n - 1) {
        if (cnt_level1 >= need_level1) {
            update_answer(answer, cur_cost);
        }
        return;
    }

    Edge &e = edges[picked[pos]];

    answer.push_back({e.id, 1});
    enumerate_types(pos + 1, cnt_level1 + 1, max(cur_cost, e.c1), answer);
    answer.pop_back();

    answer.push_back({e.id, 2});
    enumerate_types(pos + 1, cnt_level1, max(cur_cost, e.c2), answer);
    answer.pop_back();
}

void check_tree(int picked_cnt) {
    if (picked_cnt != n - 1) {
        return;
    }

    init_dsu();
    for (int i = 1; i <= picked_cnt; i++) {
        Edge &e = edges[picked[i]];
        if (!unite(e.u, e.v)) {
            return;
        }
    }

    int root = find_root(1);
    for (int i = 2; i <= n; i++) {
        if (find_root(i) != root) {
            return;
        }
    }

    vector<AnswerEdge> answer;
    enumerate_types(1, 0, 0, answer);
}

void dfs(int pos, int picked_cnt) {
    if (picked_cnt > n - 1) {
        return;
    }
    if (pos > edge_cnt) {
        check_tree(picked_cnt);
        return;
    }
    if (picked_cnt + (edge_cnt - pos + 1) < n - 1) {
        return;
    }

    picked[picked_cnt + 1] = pos;
    dfs(pos + 1, picked_cnt + 1);
    dfs(pos + 1, picked_cnt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> need_level1 >> m_input;

    edge_cnt = 0;
    int a, b, c1, c2;
    while (cin >> a >> b >> c1 >> c2) {
        edge_cnt++;
        edges[edge_cnt] = {edge_cnt, a, b, c1, c2};
    }

    dfs(1, 0);

    if (best_answer.empty()) {
        cout << -1 << '\n';
        return 0;
    }

    cout << best_cost << '\n';
    for (AnswerEdge e : best_answer) {
        cout << e.id << ' ' << e.level << '\n';
    }

    return 0;
}
