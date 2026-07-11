/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 16:55
 * update_at: 2026-07-11 17:03
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
char breed[MAXN];
int e[MAXN]; // e[i] 表示第 i 头牛名单的右端点

int first_g, first_h;
int last_g, last_h;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> n;
    cin >> s;

    for (int i = 1; i <= n; i++) {
        breed[i] = s[i - 1];
    }
    for (int i = 1; i <= n; i++) {
        cin >> e[i];
    }

    for (int i = 1; i <= n; i++) {
        if (breed[i] == 'G') {
            if (first_g == 0) {
                first_g = i;
            }
            last_g = i;
        } else {
            if (first_h == 0) {
                first_h = i;
            }
            last_h = i;
        }
    }

    bool first_g_all = (e[first_g] >= last_g);
    bool first_h_all = (e[first_h] >= last_h);

    int ans = 0;

    // 如果 G 的最早牛能覆盖所有 G，则它可以作为 G leader。
    // 此时 H leader 若不是最早 H，就只能靠名单覆盖这个 G leader。
    if (first_g_all) {
        for (int i = 1; i <= n; i++) {
            if (breed[i] == 'H' && i != first_h && i <= first_g && e[i] >= first_g) {
                ans++;
            }
        }
    }

    // 对称地处理 H 的最早牛作为 H leader 的情况。
    if (first_h_all) {
        for (int i = 1; i <= n; i++) {
            if (breed[i] == 'G' && i != first_g && i <= first_h && e[i] >= first_h) {
                ans++;
            }
        }
    }

    // 最早 G 和最早 H 组成的 pair 单独计算，避免在上面两类里重复计数。
    bool g_ok = first_g_all || (first_g <= first_h && e[first_g] >= first_h);
    bool h_ok = first_h_all || (first_h <= first_g && e[first_h] >= first_g);
    if (g_ok && h_ok) {
        ans++;
    }

    cout << ans << '\n';

    return 0;
}
