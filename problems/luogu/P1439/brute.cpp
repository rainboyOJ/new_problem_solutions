/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-19 18:44
 * update_at: 2026-09-19 18:44
 */
// brute.cpp：小数据暴力解，使用 01 序列 / 选择序列递归枚举 P1 的所有子序列。
// 每一层决定 P1 的第 dep 个数选或不选，选出来的数按原顺序放进 candidate；
// 到了叶子节点再检查 candidate 是否是 P2 的子序列，是就更新答案。
// n 到 15 左右就慢得明显，只用来对拍和理解题意。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;

int n;
int p1[MAXN], p2[MAXN];  // 两个排列，下标 1..n

int choose[MAXN];        // choose[i] 表示 P1 的第 i 个数选(1)还是不选(0)
int candidate[MAXN];     // 由 P1 中被选的数按原顺序拼成的子序列
int clen;                // candidate 的当前长度
int ans;                 // 目前找到的最长公共子序列长度

// 判断 candidate 是否是 P2 的子序列：在 P2 上顺序扫描，能依次匹配完就算成功。
bool is_subsequence_of_p2() {
    int pos = 1;
    for (int i = 1; i <= n && pos <= clen; i++) {
        if (p2[i] == candidate[pos]) pos++;
    }
    return pos > clen;
}

void dfs(int dep) {
    if (dep > n) {
        // 完整的选择序列已经生成，检查候选子序列并统计答案
        if (is_subsequence_of_p2()) {
            if (ans < clen) ans = clen;
        }
        return;
    }

    // 这一层选择 P1 的第 dep 个数：0 不选，1 选
    for (int i = 0; i <= 1; i++) {
        choose[dep] = i;
        if (i == 1) candidate[++clen] = p1[dep];
        dfs(dep + 1);
        if (i == 1) clen--;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> p1[i];
    for (int i = 1; i <= n; i++) cin >> p2[i];

    dfs(1);
    cout << ans << "\n";

    return 0;
}
