#include <bits/stdc++.h>
using namespace std;

int n, m, k;
int pack_mask[105];
int choose_pack[105]; // choose_pack[i] = 0/1，表示第 i 包糖果不买/买
int full_mask;
int ans;

int calc_mask() {
    int mask = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_pack[i] == 1) mask |= pack_mask[i];
    }
    return mask;
}

int calc_used() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_pack[i] == 1) cnt++;
    }
    return cnt;
}

bool check() {
    return calc_mask() == full_mask;
}

void dfs_choose(int dep) {
    if (dep == n + 1) {
        if (check()) {
            int value = calc_used();
            if (ans > value) ans = value;
        }
        return;
    }

    // 第 dep 包糖果的 01 选择：0 不买，1 买。
    for (int i = 0; i <= 1; i++) {
        choose_pack[dep] = i;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：枚举买哪些包糖果，统计能否覆盖所有口味。
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        int mask = 0;
        for (int j = 1; j <= k; j++) {
            int x;
            cin >> x;
            mask |= 1 << (x - 1);
        }
        pack_mask[i] = mask;
    }

    full_mask = (1 << m) - 1;
    ans = n + 1;
    dfs_choose(1);

    if (ans == n + 1) {
        cout << -1 << '\n';
    } else {
        cout << ans << '\n';
    }
    return 0;
}
