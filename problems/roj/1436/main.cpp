/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 01:00
 * update_at: 2026-10-05 01:00
 */
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

int n;       // 数列长度
ll m;        // 要求分成的段数
ll a[MAXN];  // 题目给出的数列，下标从 1 开始

// 判断上限 x 是否可行：贪心从左往右累加，放不下就另起一段，
// 返回以 x 为每段和上限时的最少段数是否不超过 m。
// 贪心正确性：每一段尽量装满，交换论证可证段数不会更多。
bool check(ll x) {
    ll cnt = 1;   // 当前已经用掉的段数，至少有一段
    ll sum = 0;   // 当前段的和
    for (int i = 1; i <= n; ++i) {
        if (sum + a[i] <= x) {
            sum += a[i];      // 还塞得进当前段
        } else {
            cnt++;            // 另起一段
            sum = a[i];
        }
    }
    return cnt <= m;
}

void solve() {
    scanf("%d %lld", &n, &m);
    ll maxa = 0, sumall = 0;   // 二分下界：至少装下最大元素；上界：一段装下全部
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
        maxa = max(maxa, a[i]);
        sumall += a[i];
    }

    // 答案 x 具有单调性：x 越大，最少段数越少，在 [maxa, sumall] 上二分
    ll lo = maxa, hi = sumall;
    while (lo < hi) {
        ll mid = (lo + hi) / 2;
        if (check(mid)) {
            hi = mid;          // 可行：答案可能是 mid 或更小
        } else {
            lo = mid + 1;      // 不可行：mid 太小
        }
    }

    printf("%lld\n", lo);
}

int main() {
    solve();
    return 0;
}
