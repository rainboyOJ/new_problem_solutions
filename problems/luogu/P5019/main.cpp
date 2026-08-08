/**
 * Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

/* P5019 [NOIP 2018 提高组] 铺设道路 */
/* 从左到右扫描，答案等于所有正向深度增量之和。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
int d[MAXN]; // 每个位置的深度

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
    }

    long long ans = d[1]; // 第一个位置需要新开 d[1] 层
    // 如果当前位置比前一个深，多出的深度必须从当前位置新开操作
    for (int i = 2; i <= n; i++) {
        if (d[i] > d[i - 1]) {
            ans += d[i] - d[i - 1];
        }
    }

    cout << ans << "\n";
    return 0;
}
