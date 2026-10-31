/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-31 18:55
 * update_at: 2026-10-31 19:03
 */
// brute.cpp：照题面直接模拟每一局，桌上用数组存点数顺序，pos[v] 记录 v 在桌上的位置。
// 每局 O(n)，总 O(n^2)，只适用于小数据。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e5 + 5;
int n, m;
int a[maxn];
int ans[maxn];

int table[maxn];   // 桌面上从左到右的点数
int pos[maxn];     // pos[v]：点数 v 在 table 中的下标，-1 表示不在桌上

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    for (int i = 1; i <= n; ++i) {
        for (int v = 1; v <= m; ++v) pos[v] = -1;
        int top = 0;                       // 桌上的牌数
        for (int j = i; j <= n; ++j) {
            int k = a[j];
            if (pos[k] != -1) {            // 桌面上有点数 k 的牌，收走它和它右边的牌
                int at = pos[k];           // 先记下位置，清空时 pos[k] 会被改成 -1
                for (int t = at; t < top; ++t) pos[table[t]] = -1;
                top = at;
            }
            table[top] = k;
            pos[k] = top;
            ++top;
        }
        for (int t = 0; t < top; ++t) ++ans[table[t]];
    }

    for (int v = 1; v <= m; ++v) {
        cout << ans[v] << (v == m ? '\n' : ' ');
    }
    return 0;
}
