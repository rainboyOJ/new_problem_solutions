/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 17:41
 * update_at: 2026-07-11 17:42
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n;
int a[MAXN], b[MAXN];
int pos_in_b[MAXN];
int relabel[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        pos_in_b[b[i]] = i;
    }

    for (int i = 1; i <= n; i++) {
        relabel[i] = pos_in_b[a[i]];
    }

    int ans = 0;
    for (int j = 1; j <= n; j++) {
        bool need_move = false;
        for (int i = 1; i < j; i++) {
            if (relabel[i] > relabel[j]) {
                need_move = true;
            }
        }
        if (need_move) {
            ans++;
        }
    }

    cout << ans << '\n';

    return 0;
}
