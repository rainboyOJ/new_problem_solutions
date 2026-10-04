/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:19
 * update_at: 2026-10-05 07:19
 */
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 200005;         // 序列长度上界
const int MAXV = 2000005;        // 盈利值 a[i] 落在 [-1e6, 1e6]，平移后统一存到该数组
const int LOGN = 19;             // 2^18 > 2e5，倍增层数最多 18 层（0..17），开 19 保险

ll n, m;                         // 月份数、询问次数
int a[MAXN];                     // a[i] 表示第 i 个月的盈利值
int last_pos[MAXV];              // last_pos[v] 表示值 v 上一次出现的位置，没出现过为 -1
int start_pos[MAXN];             // start_pos[i] 表示以 i 结尾的最长无重复区间的起始下标
int f[MAXN];                     // f[i] = i - start_pos[i] + 1，即以 i 结尾的完整无重复长度
int log2_table[MAXN];            // log2_table[x] = floor(log2(x))，供 ST 表 O(1) 查询使用
int st[LOGN][MAXN];              // st[k][i] 表示从 i 开始长度为 2^k 的区间内 f 的最大值
                                 // f 的值不超过 N = 2e5，用 int 存足够

// 预处理 start_pos、f 以及区间最大值 ST 表。
void build() {
    for (int i = 0; i < MAXV; i++) {
        last_pos[i] = -1;
    }
    for (ll i = 0; i < n; i++) {
        int v = a[i] + 1000000;              // 平移值域到非负下标
        int cur = last_pos[v] + 1;           // 起点至少要越过上一次出现的位置
        if (i > 0 && start_pos[i - 1] > cur) {
            cur = start_pos[i - 1];          // 也不能小于上一位置的起点，保证单调不降
        }
        start_pos[i] = cur;
        last_pos[v] = i;
        f[i] = i - start_pos[i] + 1;
    }
    // log2 预处理
    log2_table[1] = 0;
    for (int i = 2; i <= n; i++) {
        log2_table[i] = log2_table[i / 2] + 1;
    }
    // ST 表第一层就是 f 本身，之后按长度倍增合并
    for (ll i = 0; i < n; i++) {
        st[0][i] = f[i];
    }
    for (int k = 1; (1 << k) <= n; k++) {
        int half = 1 << (k - 1);
        for (ll i = 0; i + (1 << k) <= n; i++) {
            st[k][i] = max(st[k - 1][i], st[k - 1][i + half]);
        }
    }
}

// 查询区间 [left, right] 上 f 的最大值。
int range_max(int left, int right) {
    int k = log2_table[right - left + 1];
    int v1 = st[k][left];
    int v2 = st[k][right - (1 << k) + 1];
    return v1 > v2 ? v1 : v2;
}

// 回答一次询问区间 [L, R] 内最长完美序列的长度。
int query(int L, int R) {
    // start_pos 单调不降，二分出第一个 start_pos[mid] >= L 的位置
    int lo = L;
    int hi = R + 1;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (start_pos[mid] >= L) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    int mid = lo;
    // 左半段 [L, mid-1] 内每个 i 都受 L 截断，最大值在 i = mid-1 处，为 mid - L
    int ans_left = mid - L;
    // 右半段 [mid, R] 内不截断，取 f 的区间最大值
    int ans_right = 0;
    if (mid <= R) {
        ans_right = range_max(mid, R);
    }
    return ans_left > ans_right ? ans_left : ans_right;
}

int main() {
    scanf("%lld%lld", &n, &m);
    for (ll i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    build();
    for (ll i = 0; i < m; i++) {
        int L, R;
        scanf("%d%d", &L, &R);
        if (L > R) {
            int tmp = L;
            L = R;
            R = tmp;
        }
        printf("%d\n", query(L, R));
    }
    return 0;
}
