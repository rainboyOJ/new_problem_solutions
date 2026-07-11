/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 15:49
 * update_at: 2026-07-11 15:52
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;

int T;
int n;
int h[MAXN];
int perm_arr[MAXN];
int best[MAXN];
bool used[MAXN];
bool found;

bool produce_same_h() {
    int tmp[MAXN];
    for (int i = 1; i <= n; i++) {
        tmp[i] = perm_arr[i];
    }

    int l = 1;
    int r = n;
    for (int i = 1; i <= n - 1; i++) {
        int wrote;
        if (tmp[l] > tmp[r]) {
            wrote = tmp[l + 1];
            l++;
        } else {
            wrote = tmp[r - 1];
            r--;
        }

        if (wrote != h[i]) return false;
    }

    return true;
}

void dfs_perm(int pos) {
    if (found) return;

    if (pos == n + 1) {
        if (produce_same_h()) {
            found = true;
            for (int i = 1; i <= n; i++) {
                best[i] = perm_arr[i];
            }
        }
        return;
    }

    // 小数据暴力：按字典序递归生成所有排列，找到第一个合法排列。
    for (int x = 1; x <= n; x++) {
        if (used[x]) continue;
        used[x] = true;
        perm_arr[pos] = x;
        dfs_perm(pos + 1);
        used[x] = false;
    }
}

void solve_one() {
    cin >> n;
    for (int i = 1; i <= n - 1; i++) {
        cin >> h[i];
    }

    found = false;
    for (int i = 1; i <= n; i++) {
        used[i] = false;
        best[i] = 0;
    }

    dfs_perm(1);

    if (!found) {
        cout << -1 << '\n';
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (i > 1) cout << ' ';
        cout << best[i];
    }
    cout << '\n';
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
