/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 13:19
 * update_at: 2026-08-13 13:19
 */
// brute.cpp：小数据暴力解，把每一行选择的列号看成选择序列，先完整枚举再检查合法性。
// 与 main.cpp 的"边放边剪枝"形成对比，只适合 n <= 10 左右的小数据对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

int n;
int choose[MAXN];   // choose[i]：第 i 行皇后选择的列号（完整的选择序列）
int used_col[MAXN]; // 枚举时保证列号互不重复，形成 n 个列的排列
long long total_ans;
int printed_cnt;

// 检查当前完整选择序列是否合法：任意两行不能在同一条对角线上。
// 列号由 used_col 保证了互不重复，这里只需检查对角线冲突。
bool check() {
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (abs(i - j) == abs(choose[i] - choose[j])) {
                return false; // 行差等于列差，说明两点在同一条对角线上
            }
        }
    }
    return true;
}

void print_solution() {
    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << choose[i];
    }
    cout << '\n';
}

// 生成完整选择序列：第 dep 层决定第 dep 行皇后放在哪一列。
// 叶子节点（dep == n + 1）才统一检查合法性并统计答案。
void dfs(int dep) {
    if (dep == n + 1) {
        if (check()) {
            total_ans++;
            if (printed_cnt < 3) {
                print_solution();
                printed_cnt++;
            }
        }
        return;
    }

    // 这一层从还没用过的列里选一个，保证最终序列是一个排列。
    for (int col = 1; col <= n; col++) {
        if (used_col[col]) {
            continue;
        }
        choose[dep] = col;
        used_col[col] = 1;
        dfs(dep + 1);
        used_col[col] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    dfs(1);
    cout << total_ans << '\n';

    return 0;
}
