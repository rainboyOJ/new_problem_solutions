/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int a[105];   // 每条小鱼的可爱程度
int ans[105]; // ans[i] = 第 i 条小鱼左边比它可爱的小鱼数量
int n;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    // 对每条小鱼，枚举它左边的所有小鱼
    for (int i = 1; i <= n; i++) {
        int cnt = 0;
        for (int j = 1; j < i; j++) {
            if (a[j] < a[i]) cnt++; // 严格小于才算"不如自己可爱"
        }
        ans[i] = cnt;
    }

    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    return 0;
}
