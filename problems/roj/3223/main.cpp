/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 4005;
vector<int> graph[MAXN];
int order_[MAXN], low[MAXN], comp[MAXN];
char on_stack[MAXN];
int comp_cnt;

// Tarjan 迭代版求 SCC，返回每个点的分量编号
void scc_ids(int size) {
    for (int i = 0; i < size; i++) { order_[i] = 0; low[i] = 0; comp[i] = -1; on_stack[i] = 0; }
    vector<int> stack;
    int clock_ = 0;
    comp_cnt = 0;

    for (int root = 0; root < size; root++) {
        if (order_[root]) continue;
        vector<pair<int, int> > work;
        work.push_back(make_pair(root, 0));
        while (!work.empty()) {
            int v = work.back().first;
            int edge_at = work.back().second;
            if (!order_[v]) {
                clock_++;
                order_[v] = low[v] = clock_;
                stack.push_back(v);
                on_stack[v] = 1;
            }
            bool descended = false;
            for (int i = edge_at; i < (int)graph[v].size(); i++) {
                int w = graph[v][i];
                if (!order_[w]) {
                    work.back().second = i + 1;
                    work.push_back(make_pair(w, 0));
                    descended = true;
                    break;
                }
                if (on_stack[w]) {
                    if (order_[w] < low[v]) low[v] = order_[w];
                }
            }
            if (descended) continue;
            if (low[v] == order_[v]) {
                while (true) {
                    int w = stack.back(); stack.pop_back();
                    on_stack[w] = 0;
                    comp[w] = comp_cnt;
                    if (w == v) break;
                }
                comp_cnt++;
            }
            work.pop_back();
            if (!work.empty()) {
                int parent = work.back().first;
                if (low[v] < low[parent]) low[parent] = low[v];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;

    // liked[boy]：喜欢的姑娘（0 基）
    vector<vector<int> > liked(n);
    for (int boy = 0; boy < n; boy++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int g; cin >> g;
            liked[boy].push_back(g - 1);
        }
    }
    int init_match[4005];
    int taken_by[4005];
    for (int boy = 0; boy < n; boy++) {
        cin >> init_match[boy];
        init_match[boy]--;
    }
    for (int i = 0; i < n; i++) taken_by[i] = 0;
    for (int boy = 0; boy < n; boy++) taken_by[init_match[boy]] = boy;

    // 有向图：非匹配边 王子->姑娘，匹配边 姑娘->王子
    for (int i = 0; i < 2 * n; i++) graph[i].clear();
    for (int boy = 0; boy < n; boy++) {
        for (size_t t = 0; t < liked[boy].size(); t++) {
            int g = liked[boy][t];
            if (g != init_match[boy]) graph[boy].push_back(n + g);
        }
    }
    for (int girl = 0; girl < n; girl++)
        graph[n + girl].push_back(taken_by[girl]);

    scc_ids(2 * n);

    for (int boy = 0; boy < n; boy++) {
        vector<int> girls;
        for (size_t t = 0; t < liked[boy].size(); t++) {
            int g = liked[boy][t];
            if (g == init_match[boy] || comp[boy] == comp[n + g])
                girls.push_back(g);
        }
        sort(girls.begin(), girls.end());
        cout << girls.size();
        for (size_t t = 0; t < girls.size(); t++)
            cout << " " << girls[t] + 1;
        cout << "\n";
    }
    return 0;
}
