/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 环形仓库配对：断环成链 + 单调队列，求 max(A[i] + A[j] + (j - i))。
#include <cstdio>
#include <vector>

typedef long long ll;

int main() {
    ll n;
    if (scanf("%lld", &n) != 1) return 0; // 空输入安全返回
    std::vector<ll> a(n);
    for (ll i = 0; i < n; i++) scanf("%lld", &a[i]);

    ll reach = n / 2; // 环上每一对仓库总有一个方向距离不超过 n // 2
    std::vector<ll> chain;
    for (ll i = 0; i < n; i++) chain.push_back(a[i]);
    for (ll i = 0; i < reach; i++) chain.push_back(a[i]); // 跨过编号 n 的那一对也落进同一条链

    std::vector<ll> q(chain.size() + 1); // 存左端点下标，权值 A[i] - i 从队首到队尾严格递减
    ll head = 0, tail = 0;
    ll best = 0; // A[i] >= 1，所以 0 是安全的初值

    for (ll j = 1; j < (ll)chain.size(); j++) {
        ll i = j - 1;
        ll weight = chain[i] - i;
        while (tail > head && chain[q[tail - 1]] - q[tail - 1] <= weight) {
            tail--; // 队尾更小又更早过期，不再可能当选
        }
        q[tail++] = i;
        while (q[head] < j - reach) head++; // 距离超过 reach 的左端点滑出窗口
        ll cost = chain[q[head]] - q[head] + chain[j] + j;
        if (cost > best) best = cost;
    }
    printf("%lld\n", best);
    return 0;
}
