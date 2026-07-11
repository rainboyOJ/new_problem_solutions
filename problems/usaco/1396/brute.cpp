/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 15:57
 * update_at: 2026-07-11 15:59
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;

int n;
long long m;
string str;
char s[MAXN];
long long cap_arr[MAXN]; // 每个桶的容量
long long cur[MAXN];     // 当前牛奶量
long long nxt[MAXN];     // 下一分钟牛奶量

int pre_pos(int x) {
    if (x == 1) return n;
    return x - 1;
}

int next_pos(int x) {
    if (x == n) return 1;
    return x + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    cin >> str;
    for (int i = 1; i <= n; i++) {
        s[i] = str[i - 1];
    }

    for (int i = 1; i <= n; i++) {
        cin >> cap_arr[i];
        cur[i] = cap_arr[i];
    }

    // 小数据直接逐分钟模拟同时传奶。
    for (long long t = 1; t <= m; t++) {
        for (int i = 1; i <= n; i++) {
            nxt[i] = cur[i];
        }

        for (int i = 1; i <= n; i++) {
            if (cur[i] == 0) continue;
            nxt[i]--;
            if (s[i] == 'L') {
                nxt[pre_pos(i)]++;
            } else {
                nxt[next_pos(i)]++;
            }
        }

        for (int i = 1; i <= n; i++) {
            cur[i] = min(nxt[i], cap_arr[i]);
        }
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += cur[i];
    }

    cout << ans << '\n';

    return 0;
}
