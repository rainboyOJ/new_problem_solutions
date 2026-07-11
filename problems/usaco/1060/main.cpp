/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 13:58
 * update_at: 2026-07-11 13:59
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAXP = 1005;

int n;
int p[MAXN]; // p[i] 表示第 i 朵花的花瓣数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    int ans = 0;

    // 固定左端点，向右扩展区间，同时维护区间内出现过的花瓣数。
    for (int l = 1; l <= n; l++) {
        bool seen[MAXP];
        memset(seen, 0, sizeof(seen));

        int sum = 0;
        for (int r = l; r <= n; r++) {
            sum += p[r];
            seen[p[r]] = true;

            int len = r - l + 1;
            if (sum % len == 0) {
                int avg = sum / len;
                if (seen[avg]) {
                    ans++;
                }
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
