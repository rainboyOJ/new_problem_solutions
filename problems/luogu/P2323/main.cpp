#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
const int MAXM = 20005;

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
int fa1[MAXN], fa2[MAXN], fa_build[MAXN];

void init_dsu(int fa[]) {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
}

int find_root(int fa[], int x) {
    if (fa[x] == x) {
        return x;
    }
    fa[x] = find_root(fa, fa[x]);
    return fa[x];
}

bool unite(int fa[], int x, int y) {
    x = find_root(fa, x);
    y = find_root(fa, y);
    if (x == y) {
        return false;
    }
    fa[x] = y;
    return true;
}

bool feasible(int limit_cost) {
    init_dsu(fa1);
    init_dsu(fa2);

    int comp_all = n;
    int comp_level1 = n;

    for (int i = 1; i <= edge_cnt; i++) {
        if (edges[i].c2 <= limit_cost && unite(fa1, edges[i].u, edges[i].v)) {
            comp_all--;
        }
        if (edges[i].c1 <= limit_cost && unite(fa2, edges[i].u, edges[i].v)) {
            comp_level1--;
        }
    }

    int max_level1_edges = n - comp_level1;
    return comp_all == 1 && max_level1_edges >= need_level1;
}

vector<AnswerEdge> build_answer(int limit_cost) {
    vector<AnswerEdge> answer;
    init_dsu(fa_build);

    // 先尽量加入所有能加入的一级公路，得到一级公路子图的极大生成森林。
    for (int i = 1; i <= edge_cnt; i++) {
        if (edges[i].c1 > limit_cost) {
            continue;
        }
        if (unite(fa_build, edges[i].u, edges[i].v)) {
            answer.push_back({edges[i].id, 1});
        }
    }

    // 再用二级可行的边把各个一级公路连通块接起来。
    for (int i = 1; i <= edge_cnt; i++) {
        if ((int)answer.size() == n - 1) {
            break;
        }
        if (edges[i].c2 > limit_cost) {
            continue;
        }
        if (unite(fa_build, edges[i].u, edges[i].v)) {
            answer.push_back({edges[i].id, 2});
        }
    }

    sort(answer.begin(), answer.end(), [](const AnswerEdge &a, const AnswerEdge &b) {
        return a.id < b.id;
    });
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> need_level1 >> m_input;

    edge_cnt = 0;
    vector<int> values;
    int a, b, c1, c2;
    while (cin >> a >> b >> c1 >> c2) {
        edge_cnt++;
        edges[edge_cnt] = {edge_cnt, a, b, c1, c2};
        values.push_back(c1);
        values.push_back(c2);
    }

    if (edge_cnt == 0) {
        cout << -1 << '\n';
        return 0;
    }

    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());

    if (!feasible(values.back())) {
        cout << -1 << '\n';
        return 0;
    }

    int left = 0;
    int right = (int)values.size() - 1;
    while (left < right) {
        int mid = (left + right) >> 1;
        if (feasible(values[mid])) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    int best = values[left];
    vector<AnswerEdge> answer = build_answer(best);

    cout << best << '\n';
    for (AnswerEdge e : answer) {
        cout << e.id << ' ' << e.level << '\n';
    }

    return 0;
}
