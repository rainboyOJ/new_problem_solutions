/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 13:03
 * update_at: 2026-07-11 13:08
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n;
long long T;
long long day_arr[MAXN];
long long bale_arr[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> T;
    for (int i = 1; i <= n; i++) {
        cin >> day_arr[i] >> bale_arr[i];
    }

    long long remain = 0;
    long long answer = 0;
    int pos = 1;

    // 暴力直接逐日模拟，只适合 T 很小的数据。
    for (long long day = 1; day <= T; day++) {
        if (pos <= n && day_arr[pos] == day) {
            remain += bale_arr[pos];
            pos++;
        }

        if (remain > 0) {
            remain--;
            answer++;
        }
    }

    cout << answer << '\n';

    return 0;
}
