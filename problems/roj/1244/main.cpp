/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:30
 * update_at: 2026-10-05 06:30
 */
#include <algorithm>
#include <cstdio>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

ll a[MAXN]; // a[1..n] 存放输入的 n 个整数，排序后升序

int main() {
    ll n, m;
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    scanf("%lld", &m);

    // 升序排序后，和偏小就放弃左端，和偏大就放弃右端，
    // 行按左端点从小到大访问，首次命中即"较小的数更小"的最优数对。
    sort(a + 1, a + n + 1);
    ll i = 1;
    ll j = n;
    while (i < j) {
        ll sum = a[i] + a[j];
        if (sum < m) {
            i++; // a[i] 与任何右侧元素都配不出 m，整行放弃
        } else if (sum > m) {
            j--; // 同理整列放弃
        } else {
            printf("%lld %lld\n", a[i], a[j]);
            return 0;
        }
    }
    printf("No\n");
    return 0;
}
