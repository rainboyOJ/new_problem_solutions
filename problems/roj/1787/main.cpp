/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 02:44
 * update_at: 2026-10-08 02:44
 */
// main.cpp：ROJ 1787《保龄球》，按「球」扫描的 DP + 单调队列优化。
//
// 题意：n 个球瓶（分值可负），k 个球，每个球恰好占据连续 w 个位置（可以伸到
// 球瓶 1 左边或球瓶 n 右边的空位上），把它盖住的球瓶全部击倒并得分；一个球瓶
// 只计一次分。求最大总分。
//
// 建模：问题等价于在数轴上选 k 个长度 w 的区间，覆盖集合与 [1,n] 相交处的分值
// 之和最大。把球按右端点从小到大排序，第 j 个球相对「前 j-1 个球的最大右端点 p」
// 只有两种情况：与上一球不重叠（p ≤ i-w，整段都是新的），或与上一球重叠
// （p ∈ [i-w+1, i-1]，只有 p+1..i 是新增的）。于是只需记录「最后一个球的右端点
// 恰好是 i」这一状态，重叠项的区间最大值用单调队列摊还 O(1) 取出。

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 10005; // 球瓶数上限
const int MAXW = 105;   // 球宽上限
const int MAXPOS = MAXN + MAXW; // 右边界外补 w-1 个空位后的长度上限

int n, k, w; // 球瓶数、球数、球宽
int pos;     // 补空位后的位置总数 pos = n + w - 1

ll pre[MAXPOS];            // 前缀和，补的空位分值为 0（前缀和保持不变）
ll prevA[MAXPOS], curA[MAXPOS]; // A[i]：最后一个球右端点恰为 i 时的最大得分
ll prevB[MAXPOS], curB[MAXPOS]; // B[i]：所有球右端点都 ≤ i 时的最大得分（至多 j 个球）
int dq[MAXPOS];            // 单调队列（存下标），维护 A[p] - pre[p] 的区间最大值

const ll NEG = -(1LL << 60); // 不可达状态哨兵，远小于任何真实得分（|答案| ≤ 10^8）

// 一次投球：从位置 i 的状态推下一层，A/B 各滚动一层
void run_case() {
    scanf("%d %d %d", &n, &k, &w);
    pos = n + w - 1; // 球可以越出右边界，右端点在 n+1..n+w-1 也算合法落点
    pre[0] = 0;
    for (int i = 1; i <= n; i++) {
        ll v;
        scanf("%lld", &v);
        pre[i] = pre[i - 1] + v;
    }
    for (int i = n + 1; i <= pos; i++) pre[i] = pre[n]; // 空位不得分

    for (int i = 0; i <= pos; i++) { // 0 个球：A 不可达，B 恒为 0
        prevA[i] = NEG;
        prevB[i] = 0;
    }

    for (int j = 1; j <= k; j++) {
        int head = 0, tail = 0; // 队列区间 dq[head..tail-1]
        curA[0] = NEG;
        curB[0] = 0;
        for (int i = 1; i <= pos; i++) {
            // 第 j 个球的窗口是 [i-w+1, i]，把候选的「上一球右端点」p 全部入队
            int p = i - 1;
            ll key = prevA[p] - pre[p]; // 重叠转移里只随 p 变化的部分
            while (tail > head && prevA[dq[tail - 1]] - pre[dq[tail - 1]] <= key) tail--;
            dq[tail++] = p;

            int lo = i - w + 1; // 重叠要求上一球窗口覆盖到本窗口左端，即 p ≥ i-w+1
            if (lo < 0) lo = 0;
            while (head < tail && dq[head] < lo) head++;

            ll best = NEG;
            if (head < tail) { // 情况一：与上一球重叠，只新增 p+1..i 这段
                int bp = dq[head];
                best = pre[i] + prevA[bp] - pre[bp];
            }
            int q = i - w; // 情况二：与上一球不重叠（或球从左边界外伸进来），整段都新增
            if (q < 0) q = 0;
            ll disjoint = prevB[q] + pre[i] - pre[q];
            if (disjoint > best) best = disjoint;

            curA[i] = best;
            curB[i] = (curB[i - 1] > best) ? curB[i - 1] : best; // 至多 j 个球，位置 i 可打可不打
        }
        for (int i = 0; i <= pos; i++) { // 滚动到下一层
            prevA[i] = curA[i];
            prevB[i] = curB[i];
        }
    }
    // B 对 j 单调不减，故 B[pos][k] 就是「至多 k 个球」的答案；全负数据下它是 0
    printf("%lld\n", prevB[pos]);
}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) run_case(); // 多组数据，所有数组都在 run_case 里重置
    return 0;
}
