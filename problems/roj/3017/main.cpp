/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:17
 * update_at: 2026-10-06 14:17
 */
// main.cpp：贪心切最少段 + 倍增定位 + 二分收尾，每段校验值用「排序后最小 k 个配最大 k 个」闭式计算。
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const int MAXN = 500005;

ll a[MAXN];   // 输入的数列 A，0 基下标
ll buf[MAXN]; // 校验值计算用的临时缓冲区：把待验证的段拷进来再排序

ll n, m, limit;

// 计算 a[left .. left+len-1] 的校验值。
// 排序后取最小的 k 个与最大的 k 个反向配对，k = min(m, len/2)，
// 校验值 = 各对差的平方之和；这就是「每对差的平方之和最大」的闭式。
ll calc_value(ll left, ll len) {
    for (ll i = 0; i < len; i++) {
        buf[i] = a[left + i];
    }
    sort(buf, buf + len);
    ll k = min(m, len / 2);
    ll res = 0;
    for (ll i = 0; i < k; i++) {
        ll d = buf[len - 1 - i] - buf[i];
        res += d * d;
    }
    return res;
}

// 从 left 出发，贪心地取最长可行段：先按长度 1,2,4,... 倍增验证，
// 失败后再在「最后可行长度」和「首个失败长度」之间二分，确定段长。
ll longest_segment(ll left) {
    ll span = n - left;
    ll lo = 1; // lo 恒为已验证可行的段长（单元素段校验值为 0，必可行）
    ll hi = 2;
    while (hi <= span && calc_value(left, hi) <= limit) {
        lo = hi;
        hi <<= 1;
    }
    if (hi > span) {
        hi = span;
    }
    while (lo < hi) {
        ll mid = (lo + hi + 1) / 2;
        if (calc_value(left, mid) <= limit) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
    return lo;
}

void solve() {
    ll kase;
    cin >> kase;
    while (kase--) {
        cin >> n >> m >> limit;
        for (ll i = 0; i < n; i++) {
            cin >> a[i];
        }
        ll segments = 0;
        ll left = 0;
        while (left < n) {
            left += longest_segment(left);
            segments++;
        }
        cout << segments << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
