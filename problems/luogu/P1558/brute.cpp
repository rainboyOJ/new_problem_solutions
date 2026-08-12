/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:10
 * update_at: 2026-08-12 22:10
 */
// brute.cpp：小数据暴力解，直接模拟逐格涂色与逐格统计，用来理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int L, T, O;
int board[MAXN]; // board[i] 表示第 i 格当前的颜色编号（1..T）
bool seen[MAXN]; // seen[c] 表示颜色 c 是否在查询区间内出现

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> L >> T >> O;
    for (int i = 1; i <= L; i++)
        board[i] = 1; // 初始整块板都是颜色 1

    for (int i = 1; i <= O; i++) {
        char op;
        int a, b;
        cin >> op >> a >> b;
        if (a > b) swap(a, b); // 题目不保证 a <= b，需要交换
        if (op == 'C') {
            int c;
            cin >> c;
            // 区间涂色：暴力逐格改颜色。
            for (int j = a; j <= b; j++)
                board[j] = c;
        } else {
            // 区间查询：暴力统计出现了几种颜色。
            memset(seen, 0, sizeof(seen));
            for (int j = a; j <= b; j++)
                seen[board[j]] = true;
            int cnt = 0;
            for (int c = 1; c <= T; c++)
                if (seen[c]) cnt++;
            cout << cnt << '\n';
        }
    }
    return 0;
}
