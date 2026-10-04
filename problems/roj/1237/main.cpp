/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:20
 * update_at: 2026-10-05 06:20
 */

#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

// a[i]：原序列的值；rk[i]：离散化后的排名（第几小）
int a[MAXN];
int rk[MAXN];

// 树状数组：下标是排名，存"该排名是否已出现过"的计数
int bit[MAXN];
int n;

// 树状数组单点加 1
void bit_add(int i) {
    for (; i <= n; i += i & (-i))
        bit[i] += 1;
}

// 树状数组前缀和：排名 <= i 的已插入元素个数
int bit_sum(int i) {
    int s = 0;
    for (; i > 0; i -= i & (-i))
        s += bit[i];
    return s;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);

    // 离散化：逆序对只依赖相对大小，把值压成排名 1..n
    for (int i = 1; i <= n; ++i)
        rk[i] = a[i];
    sort(rk + 1, rk + n + 1);

    ll ans = 0;      // 完全降序时答案可达 n(n-1)/2，要用 long long
    int seen = 0;    // 已经插入树状数组的元素个数
    for (int i = 1; i <= n; ++i) {
        // 当前值的排名：第一个大于等于 a[i] 的位置（元素互不相同，即第几小）
        int pos = lower_bound(rk + 1, rk + n + 1, a[i]) - rk;
        // 前面 seen 个数中比 a[i] 大的个数 = seen - (排名 <= pos 的个数)
        ans += seen - bit_sum(pos);
        bit_add(pos);
        seen++;
    }

    printf("%lld\n", ans);
    return 0;
}
