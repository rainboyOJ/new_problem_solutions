/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 14:51
 * update_at: 2026-07-11 14:57
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

int T;
int n;
int cnt[MAXN];        // cnt[h] 表示身高 h 的奶牛数量。
int choose_h[MAXN];   // choose_h[h] = 1 表示选择身高 h 出现在照片中。
int ans;

bool check() {
    int center = 0;
    for (int h = n; h >= 1; h--) {
        if (choose_h[h] == 1) {
            center = h;
            break;
        }
    }

    if (center == 0) return false;
    if (cnt[center] == 0) return false;

    for (int h = 1; h <= n; h++) {
        if (choose_h[h] == 0 || h == center) continue;
        if (cnt[h] < 2) return false;
    }

    return true;
}

int calc_answer() {
    int center = 0;
    int value = 0;

    for (int h = n; h >= 1; h--) {
        if (choose_h[h] == 1) {
            center = h;
            break;
        }
    }

    for (int h = 1; h <= n; h++) {
        if (choose_h[h] == 0) continue;
        if (h == center) value += 1;
        else value += 2;
    }

    return value;
}

void dfs(int h) {
    if (h == n + 1) {
        if (check()) {
            int value = calc_answer();
            if (ans < value) ans = value;
        }
        return;
    }

    // 这一层决定“身高 h 是否出现在最终照片中”，只适合小 n。
    choose_h[h] = 0;
    dfs(h + 1);

    choose_h[h] = 1;
    dfs(h + 1);
}

void solve_one() {
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cnt[i] = 0;
        choose_h[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        int h;
        cin >> h;
        cnt[h]++;
    }

    ans = 0;
    dfs(1);

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        solve_one();
    }

    return 0;
}
