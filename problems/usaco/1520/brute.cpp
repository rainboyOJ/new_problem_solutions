/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 20:31
 * update_at: 2026-07-11 20:32
 */
// brute.cpp：小数据暴力解，每个询问枚举所有起点并沿父链检查。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

int n, m;
int parent_node[MAXN];
int difficulty[MAXN];
ll enjoyment[MAXN];

ll calc_path(int start, int skill, int courage) {
    int bad = 0;
    ll sum = 0;

    int u = start;
    while (u != 1) {
        if (difficulty[u] > skill) {
            bad++;
        }
        sum += enjoyment[u];
        u = parent_node[u];
    }

    if (bad <= courage) return sum;
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 2; i <= n; i++) {
        cin >> parent_node[i] >> difficulty[i] >> enjoyment[i];
    }

    cin >> m;
    for (int i = 1; i <= m; i++) {
        int skill, courage;
        cin >> skill >> courage;

        ll ans = 0;
        for (int start = 1; start <= n; start++) {
            ll value = calc_path(start, skill, courage);
            if (value > ans) ans = value;
        }
        cout << ans << '\n';
    }

    return 0;
}
