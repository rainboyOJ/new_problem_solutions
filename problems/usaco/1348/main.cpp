/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 16:17
 * update_at: 2026-07-11 16:18
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300005;

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

    int window = 2 * n + 1;
    for (int i = 1; i <= seg_cnt; i++) {
        int len = seg_len[i];
        int allowed;

        if (seg_edge[i]) {
            // 边界段可以由边界上的初始感染牛向内传播。
            allowed = 2 * len - 1;
        } else if (len % 2 == 0) {
            // 内部偶数段不能由一个奇数长度窗口完全覆盖。
            allowed = len - 1;
        } else {
            allowed = len;
        }

        window = min(window, allowed);
    }

    int ans = 0;
    for (int i = 1; i <= seg_cnt; i++) {
        ans += (seg_len[i] + window - 1) / window;
    }

    cout << ans << '\n';

    return 0;
}
