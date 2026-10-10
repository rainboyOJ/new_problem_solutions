/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 清理班次：按右端点升序的 DP，线段树维护 dp 的区间最小值。
#include <cstdio>
#include <map>
#include <vector>

typedef long long ll;

const ll INF = 1000000000LL; // 不可达哨兵：答案最多 N，与真实值不会混淆

std::vector<ll> tree;
ll seg_size;

// 把叶子 pos 的值与 value 取 min，并向上维护区间最小值
void push_min(ll pos, ll value) {
    ll i = seg_size + pos;
    if (tree[i] <= value) return;
    tree[i] = value;
    i >>= 1;
    while (i) {
        ll merged = tree[i << 1] < tree[i << 1 | 1] ? tree[i << 1] : tree[i << 1 | 1];
        if (tree[i] == merged) break; // 本节点没变，祖先自然也不会变
        tree[i] = merged;
        i >>= 1;
    }
}

// 查询下标区间 [left, right) 的最小值
ll range_min(ll left, ll right) {
    ll res = INF;
    left += seg_size;
    right += seg_size;
    while (left < right) {
        if (left & 1) {
            if (tree[left] < res) res = tree[left];
            left++;
        }
        if (right & 1) {
            right--;
            if (tree[right] < res) res = tree[right];
        }
        left >>= 1;
        right >>= 1;
    }
    return res;
}

int main() {
    ll n, T;
    if (scanf("%lld %lld", &n, &T) != 2) return 0; // 空输入安全返回

    // 右端点相同的牛只留左端点最靠左的那头，其余都被它完全支配
    std::map<ll, ll> left_of;
    for (ll i = 0; i < n; i++) {
        ll left, right;
        scanf("%lld %lld", &left, &right);
        if (left <= T) { // 一个班次都盖不到的牛直接丢弃
            std::map<ll, ll>::iterator it = left_of.find(right);
            if (it == left_of.end()) left_of[right] = left;
            else if (left < it->second) it->second = left;
        }
    }

    seg_size = 1;
    while (seg_size < T + 2) seg_size <<= 1; // dp 下标是 0..T
    tree.assign(seg_size << 1, INF);
    push_min(0, 0); // dp[0] = 0：还没铺任何班次

    for (std::map<ll, ll>::iterator it = left_of.begin(); it != left_of.end(); ++it) {
        ll right = it->first, left = it->second;
        ll covered = right < T ? right : T; // 覆盖到 T 之后再多的班次没有意义
        ll prev = range_min(left - 1, covered + 1);
        if (prev < INF) push_min(covered, prev + 1);
    }

    ll ans = range_min(T, T + 1);
    printf("%lld\n", ans < INF ? ans : -1);
    return 0;
}
