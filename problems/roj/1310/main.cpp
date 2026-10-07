/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:58
 * update_at: 2026-10-05 08:58
 */
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 10005; // 车厢数上限

int n;
int a[MAXN];       // 原始车厢顺序
int sorted_a[MAXN]; // 用于离散化的副本
int tree[MAXN];    // 权值树状数组：维护已插入元素按排名的计数

// 树状数组前缀和查询：排名 <= x 的已插入元素个数
ll query(int x) {
    ll s = 0;
    for (int i = x; i > 0; i -= i & -i) {
        s += tree[i];
    }
    return s;
}

// 树状数组单点增加：排名为 x 的位置加 1
void add(int x) {
    for (int i = x; i <= n; i += i & -i) {
        tree[i] += 1;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sorted_a[i] = a[i];
    }

    // 离散化：把车厢号映射为 1..n 的排名
    sort(sorted_a + 1, sorted_a + n + 1);
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(sorted_a + 1, sorted_a + n + 1, a[i]) - sorted_a;
    }

    ll inversions = 0; // 逆序对总数 = 最少旋转次数
    for (int i = 1; i <= n; i++) {
        // 已插入元素总数 - 比 a[i] 小或相等的已插入元素数 = 左边比 a[i] 大的元素数
        inversions += (ll)(i - 1) - query(a[i]);
        add(a[i]); // 把当前元素插入树状数组
    }

    printf("%lld\n", inversions);
    return 0;
}
