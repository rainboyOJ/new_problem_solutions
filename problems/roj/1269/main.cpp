/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:38
 * update_at: 2026-10-05 07:38
 */

#include <cstdio>

typedef long long ll;

const int MAXM = 6005;      // 拨款金额上限
const int MAXPIECE = 15000; // 二进制拆分后总份数上界：n * (log2(s)+1) ≤ 500*5

int n, m;                 // n 种奖品，拨款 m
int v[MAXPIECE];          // 每份捆绑的价格
int w[MAXPIECE];          // 每份捆绑的价值
int piece_cnt;            // 二进制拆分后总份数

ll dp[MAXM];              // dp[j]：预算不超过 j 时能取得的最大总价值

// 读取输入并把每种奖品按限购 s 二进制拆分成若干份捆绑
void read_input() {
    scanf("%d %d", &n, &m);
    piece_cnt = 0;
    for (int i = 0; i < n; ++i) {
        int price, value, stock;
        scanf("%d %d %d", &price, &value, &stock);
        // 把 stock 拆成 1, 2, 4, ..., 剩余；任取 0..stock 件都可由若干份凑出
        int k = 1;
        while (k <= stock) {
            v[piece_cnt] = k * price;
            w[piece_cnt] = k * value;
            ++piece_cnt;
            stock -= k;
            k <<= 1;
        }
        if (stock > 0) {
            v[piece_cnt] = stock * price;
            w[piece_cnt] = stock * value;
            ++piece_cnt;
        }
    }
}

// 0/1 背包：每份捆绑看成一个 0/1 物品，预算 j 从大到小保证只读旧值
void solve() {
    for (int i = 0; i < piece_cnt; ++i) {
        int cost = v[i];
        if (cost > m) continue;  // 同一奖品后续份只会更贵，跳过
        int gain = w[i];
        for (int j = m; j >= cost; --j) {
            ll cand = dp[j - cost] + gain;
            if (cand > dp[j]) dp[j] = cand;
        }
    }
    printf("%lld\n", dp[m]);
}

int main() {
    read_input();
    solve();
    return 0;
}