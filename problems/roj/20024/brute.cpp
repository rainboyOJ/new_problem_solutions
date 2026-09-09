/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 23:42
 * update_at: 2026-08-28 23:42
 */
// brute.cpp：小数据暴力解，使用 01 序列 / 选择序列递归枚举所有可能。
// 把 3*n 个格子按"行优先"拉平成一条 01 序列：choose[k] = 1 表示画 X，0 表示画 O。
// 递归只负责生成完整序列，到叶子节点再统一按题意判定每个格子是否位于三连里，
// 计算分数（红 + 蓝 -）取最大值。只能跑 n <= 4（2^(3n) 种棋盘）。
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 5;          // 暴力只处理 n <= 4
const ll NEG_INF = -(1LL << 60);

int n;
ll w[3][MAXN];               // w[行][列]：权值
int choose[3 * MAXN];        // choose[k]：第 k 个格子画什么，1 = X，0 = O
ll ans;

// 判断格子 (r,c) 是否位于"连续三个和它相同"的一线里
// 方向 4 种：横(0,1)、纵(1,0)、对角线 ↘(1,1)、对角线 ↗(1,-1)
// 对每个方向，三连中心相对 (r,c) 的偏移 m 只可能是 -1、0、1
bool in_triple(int r, int c) {
    int sym = choose[r * n + c];
    int dr[4] = {0, 1, 1, 1};
    int dc[4] = {1, 0, 1, -1};
    for (int d = 0; d < 4; d++) {
        for (int m = -1; m <= 1; m++) {
            bool ok = true;
            for (int t = -1; t <= 1; t++) {
                int rr = r + (m + t) * dr[d];
                int cc = c + (m + t) * dc[d];
                if (rr < 0 || rr >= 3 || cc < 0 || cc >= n) { ok = false; break; }
                if (choose[rr * n + cc] != sym) { ok = false; break; }
            }
            if (ok) return true;
        }
    }
    return false;
}

// 统计完整棋盘的分数：红格权值和 - 蓝格权值和，黑色格子不贡献
ll calc_answer() {
    ll sum = 0;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < n; c++) {
            if (!in_triple(r, c)) continue;            // 黑色
            int sgn = choose[r * n + c] ? 1 : -1;      // X 红 +，O 蓝 -
            sum += w[r][c] * sgn;
        }
    }
    return sum;
}

void dfs(int dep) {
    if (dep == 3 * n) {                                // 一条完整 01 序列生成完毕
        ll val = calc_answer();
        if (ans < val) ans = val;
        return;
    }
    // 这一层枚举第 dep 个格子的选择：0 = O，1 = X
    for (int i = 0; i <= 1; i++) {
        choose[dep] = i;
        dfs(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    if (n > 4) { // 超出暴力适用范围，防止越界
        cerr << "brute.cpp 仅支持 n <= 4\n";
        return 0;
    }
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < n; c++)
            cin >> w[r][c];

    ans = NEG_INF;
    dfs(0);
    cout << ans << '\n';
    return 0;
}