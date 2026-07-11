/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 16:17
 * update_at: 2026-07-11 16:18
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n;
string s;
int seg_len[MAXN];
bool seg_edge[MAXN];
int seg_cnt;

void collect_segments() {
    seg_cnt = 0;
    int i = 0;
    while (i < n) {
        if (s[i] == '0') {
            i++;
            continue;
        }

        int start = i;
        while (i < n && s[i] == '1') {
            i++;
        }
        int finish = i - 1;

        seg_cnt++;
        seg_len[seg_cnt] = finish - start + 1;
        seg_edge[seg_cnt] = (start == 0 || finish == n - 1);
    }
}

bool can_use_window(int window) {
    for (int i = 1; i <= seg_cnt; i++) {
        int len = seg_len[i];
        int allowed;

        if (seg_edge[i]) {
            allowed = 2 * len - 1;
        } else if (len % 2 == 0) {
            allowed = len - 1;
        } else {
            allowed = len;
        }

        if (window > allowed) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> s;

    collect_segments();
    if (seg_cnt == 0) {
        cout << 0 << '\n';
        return 0;
    }

    int ans = n;

    // 小数据暴力：枚举所有可能的传播窗口长度 2D+1。
    for (int window = 1; window <= 2 * n + 1; window += 2) {
        if (!can_use_window(window)) continue;

        int now = 0;
        for (int i = 1; i <= seg_cnt; i++) {
            now += (seg_len[i] + window - 1) / window;
        }
        ans = min(ans, now);
    }

    cout << ans << '\n';

    return 0;
}
