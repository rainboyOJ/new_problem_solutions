/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 15:01
 * update_at: 2026-08-14 15:45
 */
// P10841 【MX-J2-T2】Turtle and Strings
// 把 s 切成若干段，相邻段不能相同，求最大段数。
// 关键观察：存在最优解使每段长度 <= 2。
// 贪心：当前字符与上一段不同则取单字符段；
// 相同则必须取双字符段（双字符段长度 > 1，与上一段必然不同，永不冲突）。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

int n;
char s[MAXN]; // 输入字符串

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        cin >> (s + 1);

        int ans = 0;
        char last_ch = '\0'; // 上一段的第一个字符
        int last_len = 0;    // 上一段的长度
        int i = 1;
        while (i <= n) {
            if (s[i] != last_ch || last_len > 1) {
                // 单字符段与上一段不同，直接取 s[i]
                last_ch = s[i];
                last_len = 1;
                ans++;
                i++;
            } else {
                // 单字符段与上一段相同，必须取双字符段 s[i]s[i+1]
                if (i + 1 <= n) {
                    last_ch = s[i];
                    last_len = 2;
                    ans++;
                    i += 2;
                } else {
                    break; // 只剩一个字符且与上一段相同，只能并入上一段
                }
            }
        }
        cout << ans << '\n';
    }

    return 0;
}
