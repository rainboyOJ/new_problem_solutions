/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-10 14:12
 * update_at: 2026-08-10 14:12
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300;
const int MAXM = 300;

int n, m;
long long a[MAXN + 1];
int query_left[MAXM + 1];
int query_right[MAXM + 1];

// a[y] 是否是 a[x] 的全局最近值：不存在 i != x 使 |a[x]-a[i]| < |a[x]-a[y]|。
bool is_good_pair(int x, int y) {
    for (int i = 1; i <= n; i++) {
        if (i == x) continue;
        if (llabs(a[x] - a[i]) < llabs(a[x] - a[y])) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> query_left[i] >> query_right[i];
    }

    long long answer = 0;
    for (int q = 1; q <= m; q++) {
        int left = query_left[q];
        int right = query_right[q];
        int count = 0;
        // 枚举区间内所有有序对 (x,y)，x != y
        for (int x = left; x <= right; x++) {
            for (int y = left; y <= right; y++) {
                if (x == y) continue;
                if (is_good_pair(x, y)) count++;
            }
        }
        answer += (long long)count * q;
    }

    cout << answer << '\n';
    return 0;
}
