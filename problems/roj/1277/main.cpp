/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:43
 * update_at: 2026-10-04 23:43
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 15;

int n;
int a[MAXN][MAXN]; // a[i][j] 表示格子 (i, j) 上的数字（未填的格子为 0）
int f[MAXN][MAXN]; // f[i][j]：两条路各走 s-1 步、终点行号为 i 和 j 时的最大收益（s 为当前反对角线）
int nf[MAXN][MAXN]; // nf 滚动保存下一层（反对角线 s+1）的 DP 表

// 读入网格：每行三个整数 行 列 值，"0 0 0" 结束。
void read_input() {
    cin >> n;
    while (true) {
        int r, c, v;
        cin >> r >> c >> v;
        if (r == 0 && c == 0 && v == 0) break;
        a[r][c] = v; // 重复给出的格子以后出现的数为准
    }
}

void solve() {
    // 初始：两条路都在起点 A(1,1)，起点数字只计一次
    // s=2 即反对角线 i+j=2，f[1][1] 表示两条路都停在 (1,1)
    memset(f, -1, sizeof(f)); // -1 表示不可达状态（本题数值非负，可用 -1 区分）
    f[1][1] = a[1][1];

    // 两条路同步推进：走完 s-1 步时终点必在反对角线 i+j=s 上，
    // 行号 i、j 定下后列号 s-i、s-j 唯一确定，状态从四维压成三维。
    for (int s = 3; s <= 2 * n; s++) {
        memset(nf, -1, sizeof(nf));
        // 该反对角线上合法的行号范围（列号 s-i 必须落在 1..n）
        int low = max(1, s - n);
        int high = min(n, s - 1);
        for (int i = low; i <= high; i++) {
            for (int j = low; j <= high; j++) {
                // 两条路各自的上一步只能从上方或左方来，共 4 种来源组合
                int best = max(max(f[i - 1][j - 1], f[i - 1][j]),
                               max(f[i][j - 1], f[i][j]));
                if (best < 0) continue; // 前一层无可达来源
                // 终点 1 在 (i, s-i)；终点 2 在 (j, s-j)
                int gain = a[i][s - i];
                if (i != j) gain += a[j][s - j]; // i==j 说明两路停在同一格，只取一次
                if (best + gain > nf[i][j]) nf[i][j] = best + gain;
            }
        }
        // 滚动：把这一层的结果作为下一层的"上一层"
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                f[i][j] = nf[i][j];
    }

    // 两条路同时到达 B(n,n)（反对角线 s=2n 上唯一状态）
    cout << f[n][n] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
