/**
 * Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

/* P1102 A-B 数对 */
/* 排序后，对每个 a[i] 统计有多少 a[j] == a[i] + C。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int n, c;
int a[MAXN]; // 输入数组

int main() {
    cin >> n >> c;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 先排序
    sort(a + 1, a + n + 1);

    long long ans = 0;
    // 对每个 a[i]，找 a[i] + c 的出现次数
    int j = 1, k = 1;
    for (int i = 1; i <= n; i++) {
        // 用两个指针分别找等于 a[i]+c 的第一个和最后一个位置
        while (j <= n && a[j] < a[i] + c) j++;
        while (k <= n && a[k] <= a[i] + c) k++;
        // a[i]+c 的出现次数 = k - j
        ans += k - j;
    }

    cout << ans << "\n";
    return 0;
}
