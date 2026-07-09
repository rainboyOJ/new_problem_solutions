/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-09 09:44
 * update_at: 2026-07-09 09:47
 */
// brute.cpp：暴力枚举每个苹果放进哪个篮子，只适合很小的数据。
#include <bits/stdc++.h>
using namespace std;

int n, k;
long long p;
long long ans;

void dfs(int idx, int used) {
    if (idx > n) {
        if (used == k) {
            ans++;
        }
        return;
    }

    // 放进已经开好的某一个篮子。
    for (int i = 1; i <= used; i++) {
        dfs(idx + 1, used);
    }

    // 开一个新篮子给当前苹果。
    if (used < k) {
        dfs(idx + 1, used + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> p;

    ans = 0;
    dfs(1, 0);

    cout << ans % p << '\n';
    return 0;
}
