/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 10:40
 * update_at: 2026-10-03 10:40
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 做法完全照抄题面：枚举所有子串 s[l..r]（l < r），真的把这段反转出来，
// 再逐位和原串比较，统计新数字严格更小的方案数。
// 时间 O(n^3)、空间 O(n)，只适合 n 在几百以内的小数据。
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 1005;

int n;
char s[MAXN]; // 原数字串
char t[MAXN]; // 反转子串后得到的新数字串

// 逐位比较两个等长的数字串：a 是否严格小于 b（允许前导零，等长时字典序就是数值序）
bool smaller_than(const char *a, const char *b) {
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            return a[i] < b[i];
        }
    }
    return false; // 完全相同，不满足严格小于
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    n = (int)strlen(s);

    long long ans = 0;

    for (int l = 0; l < n; l++) {
        for (int r = l + 1; r < n; r++) {
            // 复制原串，再把 s[l..r] 原地反转
            for (int i = 0; i < n; i++) {
                t[i] = s[i];
            }
            for (int i = l, j = r; i < j; i++, j--) {
                char tmp = t[i];
                t[i] = t[j];
                t[j] = tmp;
            }

            if (smaller_than(t, s)) {
                ans++;
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
