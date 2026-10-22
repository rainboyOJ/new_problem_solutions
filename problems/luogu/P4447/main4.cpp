/**
 * Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-22 23:20
 * update_at: 2026-10-22 23:20
 */
// main4.cpp：第四层解法，按值域开桶 + 每个值一个堆，O(n log n)。
// 本层针对 7~8 号测试点：1 <= a_i <= 1e5，值域小，可以直接用值当下标。
//
// 层 2 的瓶颈在哪？它每个队员都要线性扫描所有链找最短的可接链，O(n^2)。
// 但「可接的链」只取决于一个东西：这条链是否以 value-1 结尾。于是按结尾值分桶：
//
//   bucket[v] = 所有以实力值 v 结尾的链，用一个小根堆存它们的长度。
//
// 处理实力值 value 的队员时，只需要看 bucket[value-1]：非空就弹出堆顶
// （堆顶就是最短的那条，规则「接最短」免费实现），接上后把长度加 1 放进
// bucket[value]；为空就新开一条长度 1 的链放进 bucket[value]。
//
// 层 2 里那些「没被接上的链自动冻结」在这里同样自动成立：
// 队员只会从 bucket[value-1] 里取，取不完的链留在原桶里不再参与延长，
// 而桶的键是结尾值，value 推进后那些桶再也不会被访问，长度自然定型。
//
// ⚠ 必须先把 a[] 排序再按这个顺序处理。规则「接最短链」只在「值从小到大」
// 的推进顺序下成立；若按输入原序处理，会先给大值建链、再回头处理小值，
// 链的接续关系就错了（例如 3 2 2 3 1 3 2 1 按原序算得 1，排序后才是 2）。
//
// ⚠ 本层把 a_i 直接当桶下标，所以只对 7~8 号测试点的值域成立（1 <= a_i <= 1e5）。
// 数据里一旦出现 a_i <= 0 或 a_i > 1e5，下标就飞出数组 —— 下面在读入时直接拦住
// 并给出明确提示，而不是让它静默越界。一般值域请用 main.cpp 的坐标压缩版本。
#include <bits/stdc++.h>
using namespace std;

const int MAXV = 100005;  // 值域上限 1e5，桶开到这个大小多留一点余量
const int MAXA = 100000;  // 7~8 号点保证 a_i <= 1e5

int n;
int a[MAXV];

// 每个实力值配一个小根堆，存「以它为结尾」的各条链长度
priority_queue<int, vector<int>, greater<int> > bucket[MAXV];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        // 本层用 a_i 直接做下标，越界就是数组越界，先拦住并说明原因
        if (a[i] < 1 || a[i] > MAXA) {
            cerr << "[main4] 本层只适用于 1 <= a_i <= " << MAXA
                 << " 的 7~8 号测试点，但读到了 a_i = " << a[i]
                 << "；请改用 main.cpp（坐标压缩版）\n";
            return 1;
        }
    }

    // 必须按实力值从小到大处理，规则「接最短链」才有意义
    sort(a + 1, a + n + 1);

    int answer = n;  // 链长的最小值即答案，先取最坏上界

    for (int i = 1; i <= n; i++) {
        int value = a[i];

        if (value >= 1 && !bucket[value - 1].empty()) {
            // 有链以 value-1 结尾，接最短的那条（堆顶）
            int len = bucket[value - 1].top() + 1;
            bucket[value - 1].pop();
            bucket[value].push(len);
        } else {
            // 没有可接的链，以 value 新开一条长度 1 的链
            bucket[value].push(1);
        }
    }

    // 扫一遍所有桶，取最小的链长
    for (int v = 0; v < MAXV; v++) {
        while (!bucket[v].empty()) {
            answer = min(answer, bucket[v].top());
            bucket[v].pop();
        }
    }

    cout << answer << '\n';
    return 0;
}
