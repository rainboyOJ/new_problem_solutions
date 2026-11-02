/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-31 18:55
 * update_at: 2026-11-02 16:25
 */
// main.cpp：每局结束的桌面等于一条「跳转链」：
//   T[i] = { a[i] } + T[ last[a[i]] + 1 ]
// 即 a[i] 这张牌一定会留在最左端，而它右侧的局面与「最后一次出现 a[i] 之后的那一局」完全相同。
//
// 把每个位置 i 连一条边 i -> last[a[i]] + 1：
//   - 每个位置出度恰好为 1；
//   - 且 last[a[i]] >= i，所以 nxt[i] >= i + 1，边严格指向更大下标 —— 无环；
//   - 所有链最终汇于哨兵 n + 1。
// 因此这其实是一片以 n + 1 为汇的「森林」（每个点唯一后继的函数图，无环特例），而不是一般 DAG。
//
// 又因为 nxt[i] > i，下标序天然就是拓扑序，于是按下标正序扫一遍、
// 沿后继「向上合并」即可：cnt[nxt[i]] += cnt[i]，得到 cnt[i] = 链经过位置 i 的局数；
// 最后按点数汇总 ans[a[i]] += cnt[i]。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5e5 + 5;
int n, m;
int a[maxn];
int last[300005]; // last[v]：点数 v 在序列中最后一次出现的位置
int nxt[maxn];    // nxt[i]：位置 i 的唯一后继 = last[a[i]] + 1（按“位置”下标存，取值 2..n+1）
ll cnt[maxn];     // cnt[i]：有多少局游戏的链经过位置 i
ll ans[300005];   // ans[v]：桌面上留有点数 v 的局数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        last[a[i]] = i; // 从左到右扫，最后一次赋值就是最后一次出现
    }

    // 建边：每个位置 i 唯一后继 nxt[i] = last[a[i]] + 1
    // 因为 last[a[i]] >= i，所以 nxt[i] >= i + 1，可能等于 n + 1（表示链到此结束）
    for (int i = 1; i <= n; ++i) {
        nxt[i] = last[a[i]] + 1;
    }

    // 初值：第 i 局一定经过位置 i，所以每个位置自己先记 1 次
    for (int i = 1; i <= n; ++i) cnt[i] = 1;
    cnt[n + 1] = 0; // 哨兵：链走到 n + 1 就结束了，累加进来不影响答案

    // 沿后继向上合并。nxt[i] > i，所以下标正序即拓扑序：
    // 轮到 i 时，所有指向 i 的点 j（都满足 j < i）都已把贡献推完，cnt[i] 已经收全
    for (int i = 1; i <= n; ++i) {
        cnt[nxt[i]] += cnt[i];
    }

    // 位置 i 上停着的牌点数是 a[i]，把经过它的局数记到对应点数上
    for (int i = 1; i <= n; ++i) {
        ans[a[i]] += cnt[i];
    }

    // 输出答案
    for (int v = 1; v <= m; ++v) {
        cout << ans[v] << (v == m ? '\n' : ' ');
    }
    return 0;
}
