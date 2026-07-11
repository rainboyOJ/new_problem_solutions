/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 20:15
 * update_at: 2026-07-11 20:16
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
int degree_cnt[MAXN]; // 无根树上的度数

int need_double_count(int children) {
    int cows = 1;
    int cnt = 0;
    while (cows < children + 1) {
        cows *= 2;
        cnt++;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n - 1; i++) {
        int a, b;
        cin >> a >> b;
        degree_cnt[a]++;
        degree_cnt[b]++;
    }

    long long ans = n - 1; // 每个非 1 号农场都需要一次移动感染。

    for (int i = 1; i <= n; i++) {
        int children = degree_cnt[i];
        if (i != 1) children--;
        if (children > 0) {
            ans += need_double_count(children);
        }
    }

    cout << ans << '\n';
    return 0;
}
