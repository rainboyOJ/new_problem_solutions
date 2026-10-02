/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-06-22 19:59
 * update_at: 2026-10-01 22:48
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 枚举所有面试顺序排列，按题意模拟录用/拒绝/放弃，只适合 n <= 9 左右。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 998244353LL;
const int MAXN = 10;

int n, m;
string s;
int c[MAXN]; // c[i]：第 i 个人的耐心上限
int p[MAXN]; // 当前枚举的面试顺序排列

// 按题意模拟当前排列：统计录用人数是否至少为 m
bool check_perm() {
    int failed = 0;
    int hired = 0;

    for (int day = 0; day < n; day++) {
        int person = p[day];

        // 之前失败人数已不少于 c_i，这个人直接放弃
        if (failed >= c[person]) {
            failed++;
            continue;
        }

        if (s[day] == '1') {
            hired++;
        }
        else {
            failed++;
        }
    }

    return hired >= m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    cin >> s;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        p[i] = i;
    }

    ll ans = 0;
    do {
        if (check_perm()) {
            ans++;
            if (ans >= MOD) {
                ans -= MOD;
            }
        }
    } while (next_permutation(p, p + n));

    cout << ans << '\n';
    return 0;
}
