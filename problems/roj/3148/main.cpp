/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 没有上司的舞会：树上最大权独立集，按后序递推每个点的两档状态。
#include <cstdio>
#include <vector>

typedef long long ll;

ll n;
std::vector<ll> happy;
std::vector<std::vector<int> > children;
std::vector<char> has_boss;
std::vector<ll> attend, absent;

int main() {
    if (scanf("%lld", &n) != 1) return 0;
    happy.assign(n + 1, 0);
    for (ll i = 1; i <= n; i++) scanf("%lld", &happy[i]);

    children.assign(n + 1, std::vector<int>());
    has_boss.assign(n + 1, 0);
    for (ll i = 0; i < n - 1; i++) {
        int child, boss;
        if (scanf("%d %d", &child, &boss) != 2) break;
        children[boss].push_back(child);
        has_boss[child] = 1;
    }
    ll root = 1;
    for (ll i = 1; i <= n; i++) {
        if (!has_boss[i]) {
            root = i;
            break;
        }
    }

    // 后序遍历整棵树：显式栈先压出「父在子前」，反转就是「子在父前」
    std::vector<int> order;
    std::vector<int> stk;
    stk.push_back((int)root);
    while (!stk.empty()) {
        int u = stk.back();
        stk.pop_back();
        order.push_back(u);
        for (size_t j = 0; j < children[u].size(); j++) stk.push_back(children[u][j]);
    }

    attend.assign(n + 1, 0);
    absent.assign(n + 1, 0);
    for (ll i = 1; i <= n; i++) attend[i] = happy[i];
    for (size_t t = order.size(); t-- > 0;) {
        int u = order[t];
        for (size_t j = 0; j < children[u].size(); j++) {
            int v = children[u][j];
            attend[u] += absent[v];                              // f[u][1] += f[儿子][0]
            absent[u] += (attend[v] > absent[v] ? attend[v] : absent[v]); // f[u][0] += max(...)
        }
    }
    printf("%lld\n", attend[root] > absent[root] ? attend[root] : absent[root]);
    return 0;
}
