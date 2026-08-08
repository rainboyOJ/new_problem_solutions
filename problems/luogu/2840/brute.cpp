// brute.cpp：小数据暴力解，递归枚举所有纸币支付序列，统计方案数（排列，顺序不同算不同方案）。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MOD = 1000000007;

int n;          // 纸币种类数
int w;          // 要凑出的金额
int a[MAXN];    // 每种纸币的面额
int answer;     // 方案数

// remain：还需要凑的金额
// 每次递归选择一张纸币，继续凑剩余金额
void dfs(int remain) {
    if (remain == 0) {
        answer = (answer + 1) % MOD;
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (remain >= a[i]) {
            dfs(remain - a[i]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> w;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    answer = 0;
    dfs(w);
    cout << answer << '\n';

    return 0;
}
