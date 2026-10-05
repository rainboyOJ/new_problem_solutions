/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 09:53
 * update_at: 2026-10-05 09:53
 */
// main.cpp：2n 个黑白棋子 + 末尾两个空位，按固定递归模式移到黑白相间排列。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 105; // n<=50 时 2n+2<=102，开 105 留余量

ll n;                       // 题目规模（白/黑棋子各 n 个）
char a[MAXN];               // a[1..2n+2] 局面，1-index；下标 0 弃用
int sp;                     // 空位起点（sp, sp+1 两个位置为空）

int st;                     // 当前步数

// 输出当前局面作为一步。
void out() {
    cout << "step" << setw(2) << right << st++ << ":";
    for (ll i = 1; i <= 2 * n + 2; i++) cout << a[i];
    cout << "\n";
}

// 把相邻棋子 a[m],a[m+1] 整体移到当前空位 (sp, sp+1)，空位随之回到 m。
void mv(int m) {
    a[sp] = a[m];
    a[sp + 1] = a[m + 1];
    a[m] = '-';
    a[m + 1] = '-';
    sp = m;
    out();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    ll size = 2 * n + 2; // 局面总长
    for (ll i = 1; i <= n; i++) a[i] = 'o';        // 前 n 个白子
    for (ll i = n + 1; i <= size; i++) a[i] = '*'; // 接下来 n 个黑子
    a[size - 1] = a[size] = '-';                   // 末尾两格空位
    sp = size - 1;

    out();                                         // step 0：初始局面

    int m = n;
    while (m > 4) {
        // n>4：先把中间的 o* 推到空位，再把 ** 推到新空位，等效把空位左推 2 格、规模减 1
        mv(m);
        mv(2 * m - 1);
        m -= 1;
    }

    // n=4：固定收尾序列
    int tail[] = {4, 8, 2, 7, 1};
    for (int i = 0; i < 5; i++) mv(tail[i]);

    return 0;
}
