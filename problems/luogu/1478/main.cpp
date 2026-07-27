/**
 * Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

/* P1478 陶陶摘苹果（升级版） */
/* 先筛掉够不到的苹果，再按消耗体力从小到大贪心摘。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;

int n, strength, chair, arm;
int cost[MAXN]; // 够得到的苹果的体力消耗
int cnt;        // 够得到的苹果数量

int main() {
    cin >> n >> strength;
    cin >> chair >> arm;
    int max_height = chair + arm;

    for (int i = 1; i <= n; i++) {
        int h, c;
        cin >> h >> c;
        // 只保留够得到的苹果
        if (h <= max_height) {
            cost[++cnt] = c;
        }
    }

    // 按体力消耗升序排序
    sort(cost + 1, cost + cnt + 1);

    int ans = 0;
    for (int i = 1; i <= cnt; i++) {
        if (strength < cost[i]) break; // 体力不够了
        strength -= cost[i];
        ans++;
    }

    cout << ans << "\n";
    return 0;
}
