/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-17 01:40
 * update_at: 2026-10-20 10:51
 */
// 佳佳的魔法药水：求 0 号药水的最小花费，以及花费最少的方案数。
// 两种得到药水的方式：直接买一份（花费 price[i]），或用配方 A+B->C 合成（花费 cost[A]+cost[B]）。
// 因为价格都是正数，合成花费严格大于两个原料各自的花费，所以配方是「两个原料都定型才能松弛」
// 的超边，仍可用 Dijkstra 的单调序处理：
//   每次弹出当前花费最小的药水并定型，再看含它的配方；
//   若配方的另一个原料也已定型（同一种原料只要求它自己定型），就用两者花费之和去松弛产物。
// 花费定型后再统计方案数：最优配方的原料一定比产物便宜，所以按花费升序扫一遍即可，
//   买一份算 1 种方案，每条满足 cost[A]+cost[B]==cost[C] 的配方贡献 ways[A]*ways[B] 种。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;    // 药水数上界 N <= 1000
const int MAXR = 500505;  // 配方数上界：无序对 (A,B) 的结果唯一，约 n(n+1)/2

int n;
long long price[MAXN];  // 商店里 1 份 i 号药水的价格
long long cost[MAXN];   // 配出 1 份 i 号药水的最小花费
bool fixed_cost[MAXN];  // i 号药水的最小花费是否已经定型（已从堆中弹出并确定）
long long ways[MAXN];   // 最小花费对应的方案数

int recipe_cnt;               // 已读入的配方数
int rec_a[MAXR];              // 配方原料 A
int rec_b[MAXR];              // 配方原料 B
int rec_c[MAXR];              // 配方产物 C
vector<int> by_potion[MAXN];  // by_potion[u]：把 u 当原料的配方编号
vector<int> by_result[MAXN];  // by_result[c]：产出 c 的配方编号

// 第一阶段：用「两个原料都定型」的 Dijkstra 求出每个药水的最小花费
void build_min_cost() {
    priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                   greater<pair<long long, int>>>
        heap;  // (花费, 药水编号)，花费在前才能按它比大小

    for (int i = 0; i < n; i++) {
        cost[i] = price[i];  // 初始候选就是「直接买」
        fixed_cost[i] = false;
        heap.push({cost[i], i});
    }

    while (!heap.empty()) {
        long long cur = heap.top().first;
        int u = heap.top().second;
        heap.pop();

        if (fixed_cost[u] || cur != cost[u]) continue;  // 已定型，或堆里是更贵的旧记录
        fixed_cost[u] = true;

        for (int idx : by_potion[u]) {
            int a = rec_a[idx];
            int b = rec_b[idx];
            int c = rec_c[idx];

            // 另一种原料也必须定型；若 A、B 是同一种药水，它自己定型就够了
            int other = (a == b) ? a : (a == u ? b : a);
            if (!fixed_cost[other]) continue;

            long long candidate = cost[a] + cost[b];
            if (candidate < cost[c]) {
                cost[c] = candidate;
                heap.push({candidate, c});
            }
        }
    }
}

// 第二阶段：按最小花费升序累计方案数
void count_ways() {
    vector<pair<long long, int>> order;  // (最小花费, 药水编号)
    for (int i = 0; i < n; i++) order.push_back({cost[i], i});
    // 最优配方的两个原料花费都严格小于产物，所以按花费升序就能保证原料先算完；
    // 花费相同的药水之间不可能互为原料，因此同花费的先后顺序不影响结果
    sort(order.begin(), order.end());

    for (const auto& item : order) {
        int u = item.second;
        long long total = (price[u] == cost[u]) ? 1 : 0;  // 直接买一份

        for (int idx : by_result[u]) {
            int a = rec_a[idx];
            int b = rec_b[idx];
            if (cost[a] + cost[b] == cost[u]) {
                // 两个原料的选法互相独立，用乘法原理组合；方案总数不超过 2^63-1，不会溢出
                total += ways[a] * ways[b];
            }
        }
        ways[u] = total;
    }
}

void read_input() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> price[i];

    // 配方行以空行结束，用 cin 读到 EOF 即可
    int a, b, c;
    while (cin >> a >> b >> c) {
        recipe_cnt++;
        rec_a[recipe_cnt] = a;
        rec_b[recipe_cnt] = b;
        rec_c[recipe_cnt] = c;
        by_potion[a].push_back(recipe_cnt);
        if (b != a) by_potion[b].push_back(recipe_cnt);  // 同一种原料只登记一次
        by_result[c].push_back(recipe_cnt);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    build_min_cost();
    count_ways();

    cout << cost[0] << ' ' << ways[0] << '\n';
    return 0;
}
