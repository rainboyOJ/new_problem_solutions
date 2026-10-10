/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 最长公共上升子序列：一次从左到右的扫描同时完成「收集候选」与「更新以 x 结尾」。
#include <cstdio>
#include <vector>
#include <algorithm>

typedef long long ll;

std::vector<ll> A, B;
std::vector<ll> shared_vals; // 两个数列的公共不同值（升序）
std::vector<ll> dp;          // dp[j]：以 b[j] 结尾的 LCIS 长度

// 把 A 里遇到的这个 x 并入 dp，返回本次写入 dp 的最大值
ll relax(ll x) {
    ll best = 0;    // 扫描到当前位置时，所有 b[j] < x 的 dp[j] 的最大值
    ll written = 0; // 本次写入的最大值，恰好就是以 x 结尾的 LCIS 长度
    for (size_t j = 0; j < B.size(); j++) {
        ll y = B[j];
        if (y < x) {
            if (dp[j] > best) best = dp[j];
        } else if (y == x) {
            written = best + 1;
            dp[j] = written; // 旧值 g(i-1, j) <= best + 1 恒成立，不必再取 max
        }
    }
    return written;
}

int main() {
    ll n;
    if (scanf("%lld", &n) != 1) return 0; // 空输入安全返回
    std::vector<ll> data;
    ll v;
    while (scanf("%lld", &v) == 1) data.push_back(v);

    ll take_a = (ll)data.size();
    if (take_a > n) take_a = n;
    A.assign(data.begin(), data.begin() + take_a);
    ll rest = (ll)data.size() - take_a;
    ll take_b = rest > n ? n : rest;
    B.assign(data.begin() + take_a, data.begin() + take_a + take_b);

    if (B.empty()) {
        printf("0\n");
        return 0;
    }

    std::vector<ll> sa = A, sb = B;
    std::sort(sa.begin(), sa.end());
    sa.erase(std::unique(sa.begin(), sa.end()), sa.end());
    std::sort(sb.begin(), sb.end());
    sb.erase(std::unique(sb.begin(), sb.end()), sb.end());
    for (size_t i = 0; i < sa.size(); i++) {
        if (std::binary_search(sb.begin(), sb.end(), sa[i])) shared_vals.push_back(sa[i]);
    }
    ll upper = (ll)shared_vals.size(); // 严格递增，答案不会超过公共不同值的个数

    dp.assign(B.size(), 0);
    ll answer = 0;
    for (size_t i = 0; i < A.size(); i++) {
        ll x = A[i];
        if (!std::binary_search(shared_vals.begin(), shared_vals.end(), x)) continue;
        ll written = relax(x);
        if (written > answer) answer = written;
        if (answer == upper) break; // 已经取到上界
    }
    printf("%lld\n", answer);
    return 0;
}
