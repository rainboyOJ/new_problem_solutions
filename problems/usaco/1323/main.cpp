/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 16:26
 * update_at: 2026-07-11 16:28
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int n;
string s;
int possible_values[MAXN];
int possible_cnt;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> s;

    int min_score = 0;
    int max_score = 0;
    bool edge_free = (s[0] == 'F' || s[n - 1] == 'F');

    for (int i = 0; i + 1 < n; i++) {
        if (s[i] != 'F' && s[i + 1] != 'F' && s[i] == s[i + 1]) {
            min_score++;
            max_score++;
        }
    }

    int i = 0;
    while (i < n) {
        if (s[i] != 'F') {
            i++;
            continue;
        }

        int l = i;
        while (i < n && s[i] == 'F') {
            i++;
        }
        int r = i - 1;
        int len = r - l + 1;

        bool has_left = (l > 0);
        bool has_right = (r + 1 < n);

        if (has_left && has_right) {
            int edge_cnt = len + 1;
            int need_odd_change = (s[l - 1] != s[r + 1]);

            // 最大值：两端相同可全相同，两端不同至少有一次变化。
            max_score += edge_cnt - need_odd_change;

            // 最小值：尽量交替；若边数奇偶不匹配，就必须留下一个相等相邻对。
            if (edge_cnt % 2 != need_odd_change) {
                min_score++;
            }
        } else {
            // 贴边的 F 段有一个自由端，可以让相等对数量从 0 到边数任意变化。
            int edge_cnt = len;
            if (!has_left && !has_right) {
                edge_cnt = len - 1;
            }
            max_score += edge_cnt;
        }
    }

    int step = edge_free ? 1 : 2;
    possible_cnt = 0;
    for (int x = min_score; x <= max_score; x += step) {
        possible_values[++possible_cnt] = x;
    }

    cout << possible_cnt << '\n';
    for (int i = 1; i <= possible_cnt; i++) {
        cout << possible_values[i] << '\n';
    }

    return 0;
}
