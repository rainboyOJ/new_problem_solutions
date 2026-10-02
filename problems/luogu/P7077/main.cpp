/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 20:59
 * update_at: 2026-10-01 21:09
 */
// main.cpp：把函数调用关系看成 DAG 做两轮处理：
// 逆拓扑序求出每个函数执行完后的整体乘法倍数 mul_all，
// 再正拓扑序把加法系数 coef 从父函数传给子函数。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;   // n <= 1e5，下标用 int 足够
const int MAXM = 100005;   // m, Q <= 1e5，函数编号用 int 足够
const ll MOD = 998244353;

int n, m, qnum;
ll a[MAXN];             // a[i]：下标 i 的数据值，最后原地变成答案
int func_type[MAXM];    // func_type[f]：函数 f 的类型 1/2/3，取值很小但仍用 int 便于读
int add_pos[MAXM];      // add_pos[f]：1 类函数要加的位置
ll func_val[MAXM];      // func_val[f]：1 类的加数 / 2 类的乘数，均已取模

// calls[f]：3 类函数按顺序调用的函数编号；
// calls[0] 是超级源点，存放题目给出的总调用序列。
vector<int> calls[MAXM];

int indeg[MAXM];        // indeg[f]：调用 DAG 上的入度，用来做拓扑排序
int work_deg[MAXM];     // work_deg[f]：拓扑排序时的工作副本，避免破坏 indeg
int order[MAXM + 1];    // order[0..order_cnt-1]：整个调用 DAG 的拓扑序
int order_cnt;

ll mul_all[MAXM];       // mul_all[f]：执行完函数 f 后整个数组额外乘上的倍数
ll coef[MAXM];          // coef[f]：函数 f 里的加法落到最终答案时还要再乘的系数
ll add_sum[MAXN];       // add_sum[p]：位置 p 收到的全部加法贡献

// 读入数据，并把总调用序列挂到超级源点 0 上。
void read_input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] %= MOD;
    }

    cin >> m;
    for (int i = 1; i <= m; i++) {
        cin >> func_type[i];
        if (func_type[i] == 1) {
            cin >> add_pos[i] >> func_val[i];
            func_val[i] %= MOD;
        } else if (func_type[i] == 2) {
            cin >> func_val[i];
            func_val[i] %= MOD;
        } else {
            int c;
            cin >> c;
            calls[i].resize(c);
            for (int j = 0; j < c; j++) {
                cin >> calls[i][j];
                indeg[calls[i][j]]++;
            }
        }
    }

    cin >> qnum;
    calls[0].resize(qnum);   // 超级源点 0 的调用序列就是题目给的总调用序列
    for (int i = 0; i < qnum; i++) {
        cin >> calls[0][i];
        indeg[calls[0][i]]++;
    }
}

// 对所有函数做一次拓扑排序，结果存入 order[]。
// 调用关系保证无环，但子函数编号可能比父函数大，所以不能只按编号顺序处理。
void build_topological_order() {
    queue<int> que;

    for (int i = 0; i <= m; i++) {
        work_deg[i] = indeg[i];
        if (work_deg[i] == 0) {
            que.push(i);
        }
    }

    order_cnt = 0;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        order[order_cnt++] = u;

        int c = calls[u].size();
        for (int i = 0; i < c; i++) {
            int v = calls[u][i];
            work_deg[v]--;
            if (work_deg[v] == 0) {
                que.push(v);
            }
        }
    }
}

// 逆拓扑序求 mul_all：函数 f 执行完后，整个数组会额外乘上的倍数。
void calc_mul_all() {
    for (int idx = order_cnt - 1; idx >= 0; idx--) {
        int u = order[idx];

        // 3 类函数的倍数就是全部子函数倍数的乘积；超级源点同理。
        ll product = 1;
        int c = calls[u].size();
        for (int i = 0; i < c; i++) {
            product = product * mul_all[calls[u][i]] % MOD;
        }

        if (u == 0) {
            mul_all[u] = product;         // 总调用序列的整体倍数
        } else if (func_type[u] == 1) {
            mul_all[u] = 1;               // 加法不改变整体倍数
        } else if (func_type[u] == 2) {
            mul_all[u] = func_val[u];     // 乘法函数的倍数就是自己的乘数
        } else {
            mul_all[u] = product;
        }
    }
}

// 正拓扑序传播 coef：父函数从后往前把系数分给子函数。
// 某个子函数后面还会执行的兄弟函数越多，它能继承到的系数就越小。
void propagate_coef() {
    coef[0] = 1;

    for (int idx = 0; idx < order_cnt; idx++) {
        int u = order[idx];
        if (u != 0 && func_type[u] != 3) {
            continue;   // 只有超级源点和 3 类函数会继续往下调用
        }

        // suffix 是当前子函数能继承的系数：它后面所有兄弟函数倍数的乘积。
        ll suffix = coef[u];
        int c = calls[u].size();
        for (int i = c - 1; i >= 0; i--) {
            int v = calls[u][i];
            coef[v] = (coef[v] + suffix) % MOD;
            suffix = suffix * mul_all[v] % MOD;
        }
    }
}

void solve() {
    build_topological_order();
    calc_mul_all();
    propagate_coef();

    // 把每个 1 类函数的加法按最终系数汇总到具体位置上。
    for (int f = 1; f <= m; f++) {
        if (func_type[f] == 1) {
            int p = add_pos[f];
            add_sum[p] = (add_sum[p] + coef[f] * func_val[f]) % MOD;
        }
    }

    // 原数组先整体乘上总调用序列的倍数，再加上所有加法贡献。
    for (int i = 1; i <= n; i++) {
        a[i] = (a[i] * mul_all[0] + add_sum[i]) % MOD;
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
