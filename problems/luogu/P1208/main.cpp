/**
 * Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

/* P1208 [USACO1.3] 混合牛奶 Mixing Milk */
/* 按单价从低到高购买，每次尽量买满当前最便宜农民的供应量。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXM = 5005;

int need, farmer_cnt;
// 农民信息：单价和供应量
int price[MAXM], amount[MAXM], idx[MAXM];

bool cmp(int a, int b) {
    return price[a] < price[b]; // 按单价升序
}

int main() {
    cin >> need >> farmer_cnt;
    for (int i = 1; i <= farmer_cnt; i++) {
        cin >> price[i] >> amount[i];
        idx[i] = i;
    }

    sort(idx + 1, idx + farmer_cnt + 1, cmp);

    int ans = 0;
    for (int i = 1; i <= farmer_cnt && need > 0; i++) {
        int id = idx[i];
        // 当前农民最多能买多少
        int buy = min(need, amount[id]);
        ans += buy * price[id];
        need -= buy;
    }

    cout << ans << "\n";
    return 0;
}
