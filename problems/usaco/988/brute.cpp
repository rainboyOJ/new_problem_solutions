/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 14:29
 * update_at: 2026-07-11 14:30
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

int n;
int b[MAXN]; // b[i] = a[i] + a[i+1]
int p[MAXN];

bool check_perm() {
    for (int i = 1; i < n; i++) {
        if (p[i] + p[i + 1] != b[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> b[i];
    }

    // 小数据暴力：按字典序枚举所有排列，第一个合法排列就是答案。
    for (int i = 1; i <= n; i++) {
        p[i] = i;
    }

    do {
        if (check_perm()) {
            for (int i = 1; i <= n; i++) {
                if (i > 1) {
                    cout << ' ';
                }
                cout << p[i];
            }
            cout << '\n';
            return 0;
        }
    } while (next_permutation(p + 1, p + n + 1));

    return 0;
}
