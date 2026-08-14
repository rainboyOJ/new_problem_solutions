/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 15:01
 * update_at: 2026-08-14 15:35
 */
// brute.cpp：小数据暴力解，使用 01 序列 / 选择序列递归枚举所有可能。
// choose[i] = 1 表示在位置 i 与 i+1 之间切一刀，
// 枚举完整切分方案后，在叶子统一检查相邻段是否相同，并统计段数取最大。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

int n;
char s[MAXN];
int choose[MAXN]; // choose[i]：位置 i 与 i+1 之间是否切一刀（1 切，0 不切）
int best;

// 检查当前切分方案是否合法（相邻段不相同），返回段数；不合法返回 -1。
int check() {
    int cnt = 1;
    int start = 1; // 当前段的起点
    for (int i = 1; i < n; i++) {
        if (choose[i] == 1) {
            // 当前段 [start, i] 结束，找下一段 [i+1, nxt] 的终点 nxt
            int nxt = i + 1;
            while (nxt < n && choose[nxt] == 0) nxt++;

            int len1 = i - start + 1; // 当前段长度
            int len2 = nxt - i;       // 下一段长度
            if (len1 == len2) {
                bool same = true;
                for (int k = 0; k < len1; k++) {
                    if (s[start + k] != s[i + 1 + k]) {
                        same = false;
                        break;
                    }
                }
                if (same) return -1; // 相邻段相同，非法
            }
            cnt++;
            start = i + 1;
        }
    }
    return cnt;
}

void dfs(int dep) {
    if (dep == n) {
        int cnt = check();
        if (cnt > best) best = cnt;
        return;
    }
    for (int i = 0; i <= 1; i++) {
        choose[dep] = i;
        dfs(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        cin >> (s + 1);

        best = 0;
        dfs(1); // 枚举位置 1..n-1 的切分选择
        cout << best << '\n';
    }

    return 0;
}
