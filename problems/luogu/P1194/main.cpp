/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-10 21:46
 * update_at: 2026-08-10 21:46
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXB = 505;
const int INF = 1e9;

int direct_cost;              // 直接购买任意一件礼物的价格 A
int gift_cnt;                 // 礼物数量 B
int discount[MAXB][MAXB];     // discount[i][j]：已买 i 后买 j 的优惠价，0 表示无优惠
int min_cost[MAXB];           // 当前把礼物 i 接入已买集合的最小代价
bool selected[MAXB];          // selected[i] 表示礼物 i 已经接入生成树

int prim() {
    for (int i = 1; i <= gift_cnt; i++) {
        // 初始时，每件礼物都可以直接买，相当于从虚拟源点连一条权值 A 的边。
        min_cost[i] = direct_cost;
        selected[i] = false;
    }

    int answer = 0;

    for (int step = 1; step <= gift_cnt; step++) {
        int u = 0;
        for (int i = 1; i <= gift_cnt; i++) {
            if (selected[i]) continue;
            if (u == 0 || min_cost[i] < min_cost[u]) {
                u = i;
            }
        }

        selected[u] = true;
        answer += min_cost[u];

        // 用新接入的礼物 u 去更新其它礼物的最小接入代价。
        for (int v = 1; v <= gift_cnt; v++) {
            if (selected[v]) continue;
            if (discount[u][v] == 0) continue; // 0 表示没有优惠边
            if (discount[u][v] < min_cost[v]) {
                min_cost[v] = discount[u][v];
            }
        }
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> direct_cost >> gift_cnt;
    for (int i = 1; i <= gift_cnt; i++) {
        for (int j = 1; j <= gift_cnt; j++) {
            cin >> discount[i][j];
        }
    }

    cout << prim() << '\n';
    return 0;
}
