/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-22 20:29
 * update_at: 2026-09-22 20:35
 */
// main.cpp：友好城市（正解，O(N log N)）。
//
// 建模：两条航道 (s1,t1)、(s2,t2) 交叉 <=> 南岸坐标的大小顺序与北岸坐标的
// 大小顺序相反。所以一个好的方案，按南岸坐标从小到大排列后，北岸坐标也
// 必须严格递增。
//
// 做法：先把所有友好城市按南岸坐标 s 从小到大排序，取出北岸坐标序列 t[]，
// 之后就是在 t[] 上求最长严格上升子序列(LIS)。
//
// LIS 写法（与 P1439 的两个排列求 LCS 一致）：
//   c[j] = 当前所有 lis值等于 j 的元素中，值(北岸坐标)最小的那个
//   f[i] = 以第 i 个元素(即 t[i]) 结尾的 lis 值
//         = 第一个满足 c[j] > t[i] 的下标 j
// 因为所有北岸坐标互不相同，c[] 严格递增，f[i] 恰好是第一个大于 t[i] 的位置。
// 二分来自 rbook《二分查找》文章的 first_true 模板，不调用 upper_bound。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5+5; // 元素个数的最大值

int n;      // 友好城市的对数
int c[maxn];// c[j] = 所有 lis值 == j 的元素中, 值最小的那个
int f[maxn];// f[i] = 以第 i 个元素(即 t[i]) 结尾的 lis 值

struct Node{
    int s; // 南岸坐标
    int t; // 北岸坐标
} a[maxn];

// 按南岸坐标从小到大排序，让"南岸的先后顺序"成为序列的固定顺序。
bool cmp_south(const Node &x, const Node &y){
    return x.s < y.s;
}

// 手写二分: 在 c[l..r] 中查找第一个满足 c[mid] > x 的位置。
// c[] 严格递增, check(mid) 形如 false false ... false true true ... true。
// 区间右端传 n+1, 位置 n+1 是虚拟位置(c[n+1] 是哨兵无穷大),
// 表示"不存在 > x 的元素"; 由于 x <= 1e6 < c[n+1], 二分不会真的返回 n+1。
int first_greater(int l, int r, int x){
    while(l < r){
        int mid = l + (r - l) / 2;
        if(c[mid] > x) r = mid;  // 答案在左半边(或就是 mid)
        else l = mid + 1;        // c[mid] <= x, mid 及左边都不可能是答案
    }
    return l;
}

// 求 a[1..n] 的北岸坐标序列的 LIS, c 与 f 的含义见上面的注释
void lis(){
    memset(c, 0x7f, sizeof(c)); // 先全部置成无穷大, 表示还没有 lis值==j 的元素
    f[1] = 1;                   // 第一对城市自己就构成长度 1 的合法方案
    c[1] = a[1].t;
    for(int i = 2; i <= n; ++i){
        f[i] = first_greater(1, n+1, a[i].t); // 以第 i 对城市结尾的 lis 值
        c[f[i]] = min(c[f[i]], a[i].t);       // lis值相同的元素里, 只保留值最小的
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> a[i].s >> a[i].t;
    }

    sort(a + 1, a + n + 1, cmp_south);

    lis();

    // 答案就是整个序列里最大的 lis 值
    int ans = 0;
    for(int i = 1; i <= n; ++i){
        ans = max(ans, f[i]);
    }
    cout << ans << "\n";
    return 0;
}
