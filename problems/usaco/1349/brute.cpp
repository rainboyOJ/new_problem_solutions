/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 16:21
 * update_at: 2026-07-11 16:23
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;
const int MAX_DAY = 1000;

int T;
int n;
long long h[MAXN];
long long a[MAXN];
int target_rank[MAXN];

bool check_days(long long days) {
    long long height[MAXN];
    for (int i = 1; i <= n; i++) {
        height[i] = h[i] + a[i] * days;
    }

    for (int i = 1; i <= n; i++) {
        int taller = 0;
        for (int j = 1; j <= n; j++) {
            if (height[j] > height[i]) {
                taller++;
            }
        }
        if (taller != target_rank[i]) {
            return false;
        }
    }

    return true;
}

int solve_one() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> target_rank[i];
    }

    // 小数据暴力：直接枚举天数，找第一个满足目标排名的时刻。
    for (int days = 0; days <= MAX_DAY; days++) {
        if (check_days(days)) {
            return days;
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cout << solve_one() << '\n';
    }

    return 0;
}
