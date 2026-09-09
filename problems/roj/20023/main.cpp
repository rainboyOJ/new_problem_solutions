/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 23:40
 * update_at: 2026-08-28 23:40
 */
// main.cpp：T3 琴(instrument) 最终解。
// 值域只有 1..50，对每个难度值 v 开一个前缀和数组，
// 每次询问从区间内出现的最小难度 mn 开始累加出现次数，遇到断档(次数为 0)就停止。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXV = 50;

int n, m;
int a[MAXN];
// pre[v][i]：前 i 个位置中难度值恰好为 v 的曲目数量
int pre[MAXV + 1][MAXN + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 预处理：每个难度值一个前缀和数组，O(n * V)
    for (int v = 1; v <= MAXV; v++) {
        for (int i = 1; i <= n; i++) {
            pre[v][i] = pre[v][i - 1] + (a[i] == v);
        }
    }

    cin >> m;
    while (m--) {
        int l, r;
        cin >> l >> r;

        // 第一步：找区间内出现的最小难度 mn
        int mn = 0;
        for (int v = 1; v <= MAXV; v++) {
            if (pre[v][r] - pre[v][l - 1] > 0) {
                mn = v;
                break;
            }
        }

        // 第二步：从 mn 开始累加各难度出现次数，遇到第一个断档(出现次数为 0)就停
        int total = 0;
        for (int v = mn; v <= MAXV; v++) {
            int cnt = pre[v][r] - pre[v][l - 1];
            if (cnt == 0) break;
            total += cnt;
        }
        cout << total << '\n';
    }

    return 0;
}
