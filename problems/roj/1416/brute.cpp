/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-17 22:52
 * update_at: 2026-10-17 22:52
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 直接按定义做：对每个询问点扫一遍所有矩形，判断 l <= x < r 且 d <= y < u，
// 命中的就 +1。复杂度 O(N * M)，只适合小数据（N、M 几百以内）。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxn = 100005;

int n, m;              // 矩形个数、询问个数
int rl[maxn], rd[maxn], rr_[maxn], ru[maxn]; // 第 i 个矩形 [l, r) x [d, u)
int qx[maxn], qy[maxn];                       // 第 j 个询问点 (x, y)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> rl[i] >> rd[i] >> rr_[i] >> ru[i];
    for (int j = 1; j <= m; j++) cin >> qx[j] >> qy[j];

    for (int j = 1; j <= m; j++) {
        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            // 半开区间：左、下边界含，右、上边界不含
            if (rl[i] <= qx[j] && qx[j] < rr_[i] && rd[i] <= qy[j] && qy[j] < ru[i]) cnt++;
        }
        printf("%d\n", cnt);
    }
    return 0;
}
