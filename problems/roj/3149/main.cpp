/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 选课：先修关系构成森林，虚拟根 0 连成树，树上背包求最高学分。
#include <cstdio>
#include <vector>

typedef long long ll;

const ll NEG = -1000000000LL; // 「这个门数凑不出来」的哨兵

ll n, m;
std::vector<std::vector<int> > children;
std::vector<ll> credits;
std::vector<std::vector<ll> > dp; // dp[v][j]：在 v 的子树里选 j 门课（必含 v）的最高学分
std::vector<ll> subtree;          // 子树节点数，用于裁剪背包循环

int main() {
    if (scanf("%lld %lld", &n, &m) != 2) return 0; // 空输入安全返回
    children.assign(n + 1, std::vector<int>());
    credits.assign(n + 1, 0);
    for (ll course = 1; course <= n; course++) {
        int prereq;
        scanf("%d %lld", &prereq, &credits[course]);
        children[prereq].push_back((int)course); // 先修课就是父亲
    }

    ll budget = m + 1; // 虚拟根 0 也占一门课的预算

    // 后序遍历（显式栈，避免深递归）
    std::vector<int> order;
    std::vector<int> stk;
    stk.push_back(0);
    while (!stk.empty()) {
        int u = stk.back();
        stk.pop_back();
        order.push_back(u);
        for (size_t j = 0; j < children[u].size(); j++) stk.push_back(children[u][j]);
    }

    dp.assign(n + 1, std::vector<ll>());
    subtree.assign(n + 1, 0);
    for (size_t t = order.size(); t-- > 0;) {
        int node = order[t];
        std::vector<ll> best(budget + 1, NEG);
        if (budget >= 1) best[1] = credits[node]; // 先备好「只选 node 自己」
        ll used = 1; // 已合并部分最多能贡献的门数
        for (size_t c = 0; c < children[node].size(); c++) {
            int child = children[node][c];
            ll sub_cap = subtree[child] < budget ? subtree[child] : budget;
            for (ll j = (used < budget ? used : budget); j >= 1; j--) { // j 倒序扫
                if (best[j] == NEG) continue;
                ll kmax = (sub_cap < budget - j) ? sub_cap : (budget - j);
                for (ll k = 1; k <= kmax; k++) {
                    ll cand = best[j] + dp[child][k];
                    if (cand > best[j + k]) best[j + k] = cand;
                }
            }
            used += sub_cap;
            if (used > budget) used = budget;
        }
        subtree[node] = used;
        dp[node] = best;
    }

    printf("%lld\n", dp[0][budget]);
    return 0;
}
