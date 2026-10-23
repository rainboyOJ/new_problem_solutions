/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 23:20
 * update_at: 2026-10-23 23:34
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
//
// 直接按题意模拟：游戏恰进行 m 个单位时间，各段步数之和恰为 m；
// 每段由一个机器人走完，段长 L ∈ [1, p]，起点工厂 i ∈ [0, n) 任选。
// 机器人在时间 s 于工厂 i 买入、走 L 步，第 l 步过马路 (i+l-1) mod n，
// 收集 w[(i+l-1) mod n][s+l]，段收益 = 收金总和 - cost[i]。
//
// 用选择序列递归枚举所有分段方式与起点工厂组合，取最大值。
//
// 为什么只适合小数据：分段方式有 2^m 量级，每段再乘 n 个起点工厂，
// n=8, m=8 时已经很慢；只用于 n, m <= 8 的对拍。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 12;
const int MAXM = 12;

int n, m, p;
ll cost[MAXN];        // cost[i]：工厂 i 的购买花费（0-based）
ll w[MAXN][MAXM];     // w[road][tm]：第 tm 个时间第 road 段马路的金币
ll best_answer;       // 全局最优解

// 从工厂 start 出发走 L 步，收集的金币总和
// 步 l 过马路 (start+l-1) mod n，收 w[...][s+l]
ll walk_gain(int start, int s, int L) {
    ll sum = 0;
    for (int l = 1; l <= L; l++) {
        int road = (start + l - 1) % n;
        sum += w[road][s + l];
    }
    return sum;
}

// 选择序列递归：dep 是当前时间（下一个机器人买入的时刻），已走完 dep 个时间单位
// 这一层在选择「下一个机器人走几步、从哪个工厂出发」
void dfs(int dep, ll cur) {
    if (dep == m) {
        if (cur > best_answer) best_answer = cur;
        return;
    }
    int maxL = min(p, m - dep);
    for (int L = 1; L <= maxL; L++) {
        for (int i = 0; i < n; i++) {
            ll g = walk_gain(i, dep, L) - cost[i];
            dfs(dep + L, cur + g);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> p;
    for (int road = 0; road < n; road++) {
        for (int tm = 1; tm <= m; tm++) {
            cin >> w[road][tm];
        }
    }
    for (int i = 0; i < n; i++) cin >> cost[i];

    best_answer = -(1LL << 60);
    dfs(0, 0);
    cout << best_answer << "\n";
    return 0;
}
