/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:07
 * update_at: 2026-10-06 15:07
 */

// main.cpp：直方图中最大的矩形，单调栈正解，与 index.md 解析一致。
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 100005; // 每个用例最多 1e5 根柱子，再加 1 个哨兵

ll h[MAXN]; // h[i]：第 i 根柱子的高度，下标从 0 开始，末尾补一个高度 0 的哨兵
ll stk[MAXN]; // stk：单调递增栈，只存柱子下标
ll topIdx; // 栈顶指针（从 1 开始用，0 表示空栈，避免和柱子下标混淆）

int main() {
    ll n;
    while (cin >> n) {
        if (n == 0) break; // n=0 结束输入，不处理
        for (ll i = 0; i < n; i++) cin >> h[i];
        h[n] = 0; // 哨兵：保证扫描结束时栈里剩下的柱子全被弹出结算

        ll ans = 0;
        topIdx = 0;
        for (ll i = 0; i <= n; i++) {
            // 弹出条件带等号：等高的柱子让先弹出的那个宽度算小一点，
            // 但最后留着的同高柱子结算时会把这些列一起算进去，面积不丢
            while (topIdx > 0 && h[i] <= h[stk[topIdx]]) {
                ll j = stk[topIdx]; topIdx--; // 弹出的柱子 j：右边界就是 i
                ll left = topIdx > 0 ? stk[topIdx] : -1; // 左边第一个更矮的柱子
                ll area = h[j] * (i - left - 1); // 以 h[j] 为高，宽为开区间 (left, i) 的长度
                ans = max(ans, area);
            }
            topIdx++; stk[topIdx] = i; // 当前下标入栈
        }
        cout << ans << "\n";
    }
    return 0;
}
