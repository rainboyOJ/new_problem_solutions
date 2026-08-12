/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 23:00
 * update_at: 2026-08-12 22:12
 */
// brute.cpp：小数据暴力解，使用 01 序列递归枚举候选串 S，用来理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAX_LEN = 35;

int n, m, q;
char str[MAXN][MAX_LEN]; // str[i]：第 i 年信的内容（0 / 1 / ?）
int choose[MAX_LEN];     // choose[j]：候选串 S 第 j 位的取值，0 或 1

// 检查当前完整候选串 choose[0..n-1] 是否兼容 [l, r] 内的所有信。
// 对每个位置：信里是 '0' 则 S 该位必须为 0，是 '1' 则必须为 1，是 '?' 则无限制。
bool check(int l, int r) {
    for (int i = l; i <= r; i++) {
        for (int j = 0; j < n; j++) {
            if (str[i][j] != '?' && str[i][j] - '0' != choose[j])
                return false;
        }
    }
    return true;
}

// dfs(dep)：这一层枚举候选串第 dep 位取 0 还是 1。
// 生成完整 n 位候选串后，在叶子节点统一检查并统计答案。
void dfs(int dep, int l, int r, int& cnt) {
    if (dep == n) {
        if (check(l, r))
            cnt++;
        return;
    }
    for (int b = 0; b <= 1; b++) {
        choose[dep] = b;
        dfs(dep + 1, l, r, cnt);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q;
    for (int i = 1; i <= m; i++)
        cin >> str[i];

    int ans_xor = 0; // 所有查询答案的异或和
    while (q--) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            // 修改：直接覆盖第 pos 年的信
            int pos;
            cin >> pos >> str[pos];
        } else {
            // 查询：枚举全部 2^n 个候选串 S，统计与 [l, r] 内所有信兼容的个数
            int l, r, cnt = 0;
            cin >> l >> r;
            dfs(0, l, r, cnt);
            ans_xor ^= cnt;
        }
    }
    cout << ans_xor << '\n';
    return 0;
}
