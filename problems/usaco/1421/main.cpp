/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 15:49
 * update_at: 2026-07-11 15:52
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int T;
int n;
int h[MAXN];
int ans[MAXN];
bool used[MAXN];

bool check_answer() {
    int l = 1;
    int r = n;

    for (int i = 1; i <= n - 1; i++) {
        int wrote;
        if (ans[l] > ans[r]) {
            wrote = ans[l + 1];
            l++;
        } else {
            wrote = ans[r - 1];
            r--;
        }

        if (wrote != h[i]) return false;
    }

    return true;
}

void solve_one() {
    cin >> n;
    for (int i = 1; i <= n - 1; i++) {
        cin >> h[i];
    }

    if (h[n - 1] != 1) {
        cout << -1 << '\n';
        return;
    }

    for (int i = 1; i <= n; i++) {
        used[i] = false;
        ans[i] = 0;
    }

    bool ok = true;
    for (int i = 1; i <= n - 2; i++) {
        if (used[h[i]]) ok = false;
        used[h[i]] = true;
    }

    if (!ok) {
        cout << -1 << '\n';
        return;
    }

    int ends[3];
    int end_cnt = 0;
    for (int x = 1; x <= n; x++) {
        if (!used[x]) {
            end_cnt++;
            ends[end_cnt] = x;
        }
    }

    if (end_cnt != 2) {
        cout << -1 << '\n';
        return;
    }

    ans[1] = ends[1];
    ans[n] = ends[2];

    int l = 1;
    int r = n;
    for (int i = 1; i <= n - 2; i++) {
        if (ans[l] > ans[r]) {
            l++;
            ans[l] = h[i];
        } else {
            r--;
            ans[r] = h[i];
        }
    }

    if (!check_answer()) {
        cout << -1 << '\n';
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (i > 1) cout << ' ';
        cout << ans[i];
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
