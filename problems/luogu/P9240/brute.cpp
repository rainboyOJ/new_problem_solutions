/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 11:36
 * update_at: 2026-10-03 11:36
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 做法：把转换率 V 的每个候选值都试一遍，逐条记录检查 A_i / V 是否恰好等于 B_i，
// 记下所有可行 V 中最小的和最大的。
// 候选范围只做一次最朴素的剪枝：由 B_i = A_i / V 可知 V * B_i <= A_i，
// 所以 V 不会超过 min(A_i / B_i)，枚举 1 到这个上界即可。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 105;

int n;
ll a[MAXN]; // 第 i 条记录投入的普通金属 O
ll b[MAXN]; // 第 i 条记录炼出的特殊金属 X

// 检查猜测的转换率 v 是否能解释全部冶炼记录。
bool check(ll v) {
    for (int i = 1; i <= n; i++) {
        if (a[i] / v != b[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
    }

    // 朴素上界：V <= A_i / B_i 对每条记录都成立，取最小值。
    ll up = a[1] / b[1];
    for (int i = 2; i <= n; i++) {
        if (a[i] / b[i] < up) up = a[i] / b[i];
    }

    ll first = 0; // 最小的可行 V，0 表示暂时没找到
    ll last = 0;  // 最大的可行 V
    for (ll v = 1; v <= up; v++) {
        if (check(v)) {
            if (first == 0) first = v;
            last = v;
        }
    }

    cout << first << " " << last << "\n";
    return 0;
}
