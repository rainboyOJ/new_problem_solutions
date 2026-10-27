/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-27 17:04
 * update_at: 2026-10-27 17:04
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 每次询问直接从 l 往右逐个数检查，遇到第一个大于 k 的就停下，单次 O(r-l+1)。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2000000 + 5;

int n, m;
int a[MAXN]; // a[i] 只有 2e6 以内且只做大小比较，用 int 省内存

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 1; i <= m; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        int answer = -1; // 找不到答案时输出 -1
        for (int j = l; j <= r; j++) {
            if (a[j] > k) {
                answer = j; // 从左往右第一个满足条件的下标
                break;
            }
        }
        cout << answer << '\n';
    }

    return 0;
}
