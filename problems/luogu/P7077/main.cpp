#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXM = 100005;
const int MOD = 998244353;

int n;
int a[MAXN];
int m;
int typ[MAXM];      // typ[i] : 第 i 个函数的类型
int pos_[MAXM];     // type1 修改的位置
int val_[MAXM];     // type1 / type2 的参数
vector<int> calls[MAXM]; // type3 按顺序调用的函数列表

int qnum;
vector<int> queries;

vector<int> graph[MAXM];
int indeg[MAXM];
int mul[MAXM];      // mul[i] : 执行完函数 i 后，对整个数组的整体乘法效果
int coef[MAXM];     // coef[i] : 函数 i 中 type1 加法最终要乘上的系数
int add_sum[MAXN];  // add_sum[p] : 所有对位置 p 的加法总贡献

void read_input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    cin >> m;
    for (int i = 0; i <= m; i++) {
        graph[i].clear();
        indeg[i] = 0;
        calls[i].clear();
        mul[i] = 1;
        coef[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        add_sum[i] = 0;
    }

    for (int i = 1; i <= m; i++) {
        cin >> typ[i];
        if (typ[i] == 1) {
            cin >> pos_[i] >> val_[i];
            val_[i] %= MOD;
        } else if (typ[i] == 2) {
            cin >> val_[i];
            val_[i] %= MOD;
        } else {
            int c;
            cin >> c;
            calls[i].resize(c);
            for (int j = 0; j < c; j++) {
                cin >> calls[i][j];
                graph[i].push_back(calls[i][j]);
                indeg[calls[i][j]]++;
            }
        }
    }

    cin >> qnum;
    queries.resize(qnum);
    for (int i = 0; i < qnum; i++) {
        cin >> queries[i];
        graph[0].push_back(queries[i]);
        indeg[queries[i]]++;
    }
}

vector<int> get_topological_order() {
    queue<int> q;
    vector<int> deg(m + 1);
    vector<int> order;

    for (int i = 0; i <= m; i++) {
        deg[i] = indeg[i];
        if (deg[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);

        for (int v : graph[u]) {
            deg[v]--;
            if (deg[v] == 0) {
                q.push(v);
            }
        }
    }

    return order;
}

void calc_mul(const vector<int> &order) {
    for (int idx = (int) order.size() - 1; idx >= 0; idx--) {
        int u = order[idx];

        if (u == 0) {
            long long ret = 1;
            for (int v : queries) {
                ret = ret * mul[v] % MOD;
            }
            mul[u] = ret;
        } else if (typ[u] == 1) {
            mul[u] = 1;
        } else if (typ[u] == 2) {
            mul[u] = val_[u];
        } else {
            long long ret = 1;
            for (int v : calls[u]) {
                ret = ret * mul[v] % MOD;
            }
            mul[u] = ret;
        }
    }
}

void propagate_coef(const vector<int> &order) {
    coef[0] = 1;

    for (int u : order) {
        long long cur = coef[u];

        if (u == 0) {
            for (int i = qnum - 1; i >= 0; i--) {
                int v = queries[i];
                coef[v] = (coef[v] + cur) % MOD;
                cur = cur * mul[v] % MOD;
            }
        } else if (typ[u] == 3) {
            for (int i = (int) calls[u].size() - 1; i >= 0; i--) {
                int v = calls[u][i];
                coef[v] = (coef[v] + cur) % MOD;
                cur = cur * mul[v] % MOD;
            }
        }
    }
}

void solve() {
    vector<int> order = get_topological_order();
    calc_mul(order);
    propagate_coef(order);

    for (int i = 1; i <= m; i++) {
        if (typ[i] == 1) {
            int p = pos_[i];
            add_sum[p] = (add_sum[p] + 1LL * coef[i] * val_[i]) % MOD;
        }
    }

    for (int i = 1; i <= n; i++) {
        a[i] = (1LL * a[i] * mul[0] + add_sum[i]) % MOD;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';

    return 0;
}
