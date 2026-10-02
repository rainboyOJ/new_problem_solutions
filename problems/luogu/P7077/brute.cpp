/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 20:59
 * update_at: 2026-10-01 21:09
 */
// brute.cpp：小数据暴力解，直接递归模拟每个函数的效果，用来理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 105;   // 暴力只服务小数据，n 取到 100 左右
const int MAXM = 105;   // 函数个数同样只到小规模
const ll MOD = 998244353;

int n, m, qnum;
ll a[MAXN];             // a[i]：下标 i 的数据值，模拟过程中不断更新
int func_type[MAXM];    // func_type[f]：函数 f 的类型 1/2/3
int add_pos[MAXM];      // add_pos[f]：1 类函数要加的位置
ll func_val[MAXM];      // func_val[f]：1 类的加数 / 2 类的乘数
vector<int> calls[MAXM]; // calls[f]：3 类函数按顺序调用的函数编号
int query_list[MAXM];   // query_list[i]：总调用序列里的第 i 个函数

// 递归执行函数 id 的全部效果：1 类单点加，2 类整体乘，3 类按顺序递归子函数。
void exec_func(int id) {
    if (func_type[id] == 1) {
        a[add_pos[id]] = (a[add_pos[id]] + func_val[id]) % MOD;
    } else if (func_type[id] == 2) {
        for (int i = 1; i <= n; i++) {
            a[i] = a[i] * func_val[id] % MOD;
        }
    } else {
        int c = calls[id].size();
        for (int i = 0; i < c; i++) {
            exec_func(calls[id][i]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

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
            }
        }
    }

    cin >> qnum;
    for (int i = 0; i < qnum; i++) {
        cin >> query_list[i];
    }

    // 照题目要求依次执行整个调用序列，直接得到答案。
    for (int i = 0; i < qnum; i++) {
        exec_func(query_list[i]);
    }

    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';

    return 0;
}
