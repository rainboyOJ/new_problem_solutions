/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-05 13:30
 * update_at: 2026-08-05 13:30
 */
// brute.cpp：小数据暴力解，O(n^2) 求每个圆盘的下一个更大直径，询问沿链模拟。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, q;
long long D[MAXN], C[MAXN];
int nxt[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> D[i] >> C[i];

    // 直接向后找第一个直径更大的圆盘
    for (int i = 1; i <= n; i++) {
        nxt[i] = 0;
        for (int j = i + 1; j <= n; j++)
            if (D[j] > D[i]) {
                nxt[i] = j;
                break;
            }
    }

    for (int t = 0; t < q; t++) {
        int r;
        long long v;
        cin >> r >> v;

        int cur = r;
        long long need = v;
        while (true) {
            if (C[cur] >= need) {   // 当前圆盘装得下：停在这
                cout << cur << '\n';
                break;
            }
            need -= C[cur];         // 装满并溢出
            cur = nxt[cur];
            if (cur == 0) {         // 下面没有更大的圆盘：流入水池
                cout << 0 << '\n';
                break;
            }
        }
    }

    return 0;
}
