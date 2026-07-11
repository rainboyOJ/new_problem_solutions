/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 12:56
 * update_at: 2026-07-11 12:57
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, m;
long long height_cow[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> height_cow[i];
    }

    for (int j = 1; j <= m; j++) {
        long long candy;
        cin >> candy;
        long long eaten = 0;

        // 暴力直接让每头牛都尝试一次，不提前跳出。
        for (int i = 1; i <= n; i++) {
            if (height_cow[i] > eaten) {
                long long top = min(height_cow[i], candy);
                long long add = top - eaten;
                height_cow[i] += add;
                eaten = top;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << height_cow[i] << '\n';
    }

    return 0;
}
