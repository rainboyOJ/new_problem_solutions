/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:30
 * update_at: 2026-10-05 23:30
 */
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

ll n;               // 隔间数量
ll c;               // 牛的数量
ll stall[MAXN];     // stall[i] 表示第 i 个隔间的位置（排序后使用）

// 判定间距至少为 dist 时能否放下 c 头牛。
// 贪心：第一头牛放在最左隔间，之后每头都放在第一个距离上一头牛至少 dist 的隔间。
// 每头牛都尽量往左压，给后面的牛留出最大剩余空间，因此这种摆法可行等价于真正可行。
bool can_place(ll dist) {
    ll placed = 1;          // 最左隔间必放一头
    ll last = stall[1];     // 上一头牛所在的隔间位置
    for (ll i = 2; i <= n; i++) {
        if (stall[i] - last >= dist) {
            last = stall[i];
            placed++;
        }
    }
    return placed >= c;
}

int main() {
    scanf("%lld %lld", &n, &c);
    for (ll i = 1; i <= n; i++) {
        scanf("%lld", &stall[i]);
    }
    sort(stall + 1, stall + n + 1);

    // 题面只保证 0 <= xi <= 1e9，没保证位置互不相同。
    // 若不同位置不足 c 个，必有一对牛同处一室，最小距离只能是 0，
    // 下面的 [1, hi] 二分区间覆盖不到这个答案。
    ll distinct = 1;
    for (ll i = 2; i <= n; i++) {
        if (stall[i] != stall[i - 1]) {
            distinct++;
        }
    }
    if (distinct < c) {
        printf("0\n");
        return 0;
    }

    // 可行性关于 dist 单调（dist 越小越容易放下），所以二分最大的可行间距。
    // 上界：c 头牛两两间距 >= d 时首尾至少隔开 (c-1)*d，不超过总跨度。
    ll lo = 1;
    ll hi = (stall[n] - stall[1]) / (c - 1);
    while (lo < hi) {
        ll mid = (lo + hi + 1) / 2;   // 上取整，配合 lo = mid 避免死循环
        if (can_place(mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
    printf("%lld\n", lo);
    return 0;
}
