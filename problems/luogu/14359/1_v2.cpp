// 60 分做法（新思路）：双重循环枚举所有合法区间 + P1803 区间贪心
//
// 思路：
//   1. 利用异或性质 a^a=0，用前缀异或 pre[r] ^ pre[l-1] 快速求区间异或和
//   2. 双重 for 循环枚举所有异或和为 k 的区间 [l, r]
//   3. 把每个合法区间记为一条线段，问题转化为"最大不相交区间数量"
//   4. 按右端点排序 + 贪心选择（经典 P1803 区间贪心）
//
// 复杂度 O(n² + m log m)，其中 m 是合法区间数量，n ≤ 2000 时可接受
// 保留原 1.cpp 不动，本文件为新写法
#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e6 + 5;

struct Segment {
    int l; // 区间左端点
    int r; // 区间右端点
};

int n, k;
int a[maxn];
int pre[maxn];          // pre[i] = a[1] ^ a[2] ^ ... ^ a[i]
int m;                  // 合法区间数量
Segment seg[maxn];      // 存储所有合法区间

// 按右端点从小到大排序，右端点相同时按左端点从小到大排序
bool cmp_segment(const Segment &x, const Segment &y) {
    if (x.r != y.r) {
        return x.r < y.r;
    }
    return x.l < y.l;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = pre[i - 1] ^ a[i]; // 计算前缀异或
    }

    // 双重循环枚举所有合法区间
    // 利用性质：区间 [l, r] 的异或和 = pre[r] ^ pre[l-1]
    m = 0;
    for (int l = 1; l <= n; l++) {
        for (int r = l; r <= n; r++) {
            if ((pre[r] ^ pre[l - 1]) == k) {
                m++;
                seg[m].l = l;
                seg[m].r = r;
            }
        }
    }

    // 按右端点排序，贪心选择不相交区间（P1803 核心）
    sort(seg + 1, seg + m + 1, cmp_segment);

    int ans = 0;
    int last_end = 0; // 上一个已选区间的右端点
    for (int i = 1; i <= m; i++) {
        // 当前区间左端点 > 上一个已选区间的右端点，说明不重叠
        if (seg[i].l > last_end) {
            ans++;
            last_end = seg[i].r;
        }
    }

    cout << ans << '\n';
    return 0;
}
