/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXC = 40005;

int n, m, target;
int basic_cost[MAXN];   // 仓库 i 的基本运费
int piece_cost[MAXN];   // 仓库 i 每件货物的计件运费
vector<int> goods[MAXN]; // goods[i] 存放仓库 i 中所有货物的价值
int dp[MAXC];    // dp[c] 表示恰好花费 c 时能获得的最大净现金
int next_dp[MAXC]; // 处理当前仓库时的滚动数组

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> target;
    for (int i = 0; i < n; i++) cin >> basic_cost[i] >> piece_cost[i];
    for (int i = 0; i < m; i++) {
        int value, warehouse;
        cin >> value >> warehouse;
        goods[warehouse].push_back(value);
    }

    // 同一仓库选 k 件时应取价值最高的 k 件，先降序排序；同时算出最大可能花费
    int maximum_cost = 0;
    for (int i = 0; i < n; i++) {
        if (goods[i].empty()) continue;
        sort(goods[i].begin(), goods[i].end(), greater<int>());
        maximum_cost += basic_cost[i] + piece_cost[i] * (int)goods[i].size();
    }

    // 分组背包：把每个仓库看作一组，组内选项是“选前 k 件”的所有 k
    const int NEG_INF = -1000000000;
    for (int c = 0; c <= maximum_cost; c++) dp[c] = NEG_INF;
    dp[0] = 0;

    for (int warehouse = 0; warehouse < n; warehouse++) {
        if (goods[warehouse].empty()) continue;
        // next_dp 先复制 dp，表示“不选这个仓库”的情况
        for (int c = 0; c <= maximum_cost; c++) next_dp[c] = dp[c];

        int profit = -basic_cost[warehouse];
        for (int count = 1; count <= (int)goods[warehouse].size(); count++) {
            profit += goods[warehouse][count - 1] - piece_cost[warehouse]; // 选前 count 件的净现金
            int cost = basic_cost[warehouse] + count * piece_cost[warehouse];
            // 从旧 dp 转移，保证同一仓库的不同选项互斥
            for (int old_cost = 0; old_cost + cost <= maximum_cost; old_cost++) {
                if (dp[old_cost] == NEG_INF) continue;
                if (next_dp[old_cost + cost] < dp[old_cost] + profit) {
                    next_dp[old_cost + cost] = dp[old_cost] + profit;
                }
            }
        }
        for (int c = 0; c <= maximum_cost; c++) dp[c] = next_dp[c];
    }

    // 找满足净现金 >= target 的最小花费
    int answer = maximum_cost;
    for (int c = 0; c <= maximum_cost; c++) {
        if (dp[c] >= target && c < answer) answer = c;
    }
    cout << answer << '\n';

    return 0;
}