/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 20:58
 * update_at: 2026-07-11 21:00
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n;
string s;
long long answer_cnt[MAXN];
bool marked[MAXN];

int compare_sub(int i, int j, int len) {
    for (int k = 0; k < len; k++) {
        if (s[i + k] < s[j + k]) return -1;
        if (s[i + k] > s[j + k]) return 1;
    }
    return 0;
}

int calc_pair(int big_len, int small_len) {
    for (int i = 0; i < n; i++) {
        marked[i] = false;
    }

    for (int start = 0; start + big_len <= n; start++) {
        int best_pos = start;
        for (int p = start + 1; p + small_len <= start + big_len; p++) {
            if (compare_sub(p, best_pos, small_len) < 0) {
                best_pos = p;
            }
        }
        marked[best_pos] = true;
    }

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (marked[i]) cnt++;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s;

    for (int big_len = 1; big_len <= n; big_len++) {
        for (int small_len = 1; small_len <= big_len; small_len++) {
            int cnt = calc_pair(big_len, small_len);
            answer_cnt[cnt]++;
        }
    }

    for (int v = 1; v <= n; v++) {
        cout << answer_cnt[v] << '\n';
    }

    return 0;
}
