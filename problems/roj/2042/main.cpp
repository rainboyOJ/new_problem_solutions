/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:33
 * update_at: 2026-10-06 09:33
 */

// 丑数：质因数全部取自给定素数集合 S 的正整数（1 不算）。
// 多路归并：每个素数 p_j 对应一条候选队列 a[0]*p_j, a[1]*p_j, ...（a[0]=1 只是起点），
// 队列单调递增，用下标 idx[j] 表示已用掉几个乘数；下一个丑数是 K 个队首的最小值。
// 用小根堆取最小，O(N log K)。

#include <cstdio>
#include <queue>
#include <vector>

typedef long long ll;

const int MAXK = 105;
const int MAXN = 100005;

int k, n;
int p[MAXK];    // p[j]：素数集合 S 的第 j 个素数（下标从 0 开始）
ll idx[MAXK];   // idx[j]：素数 p_j 已经用掉的乘数个数，当前候选是 a[idx[j]] * p[j]
ll a[MAXN];     // a[0]=1 只是乘数起点不算丑数，a[i] 是从小到大第 i 个丑数

// 堆元素 (候选值, 素数下标)：小根堆按候选值比较，弹出后才知道该推进哪个素数
struct Cand {
    ll v;
    int j;
};

// 堆的比较器：候选值小的先出堆
struct CandCmp {
    bool operator()(const Cand &x, const Cand &y) const {
        return x.v > y.v;
    }
};

std::priority_queue<Cand, std::vector<Cand>, CandCmp> heap;

// 多路归并：循环 n 轮，每轮取堆顶最小候选作为下一个丑数，
// 打平（多个队列同时给出最小值）的队列一起推进，避免重复产出
ll solve() {
    a[0] = 1; // 乘数起点哨兵，本身不算丑数
    for (int j = 0; j < k; j++) {
        idx[j] = 0;
        Cand c;
        c.v = p[j];
        c.j = j;
        heap.push(c); // 每条队列的初始候选 a[0] * p[j] = p[j]
    }

    for (int i = 1; i <= n; i++) {
        ll cur = heap.top().v; // 所有队首的最小值就是下一个丑数
        a[i] = cur;
        // 把所有等于 cur 的队首都推进一格：它们已经交付过 cur，不许再交付第二次
        while (heap.top().v == cur) {
            int j = heap.top().j;
            heap.pop();
            idx[j]++;
            Cand c;
            c.v = a[idx[j]] * p[j]; // 新候选引用刚生成的 cur，因而严格大于 cur
            c.j = j;
            heap.push(c);
        }
    }
    return a[n];
}

int main() {
    scanf("%d %d", &k, &n);
    for (int j = 0; j < k; j++) scanf("%d", &p[j]);
    printf("%lld\n", solve());
    return 0;
}
