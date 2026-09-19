/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-19 18:44
 * update_at: 2026-09-19 18:44
 */
// main.cpp：两个排列的最长公共子序列。
//
// 建模：把 P1 的每个值映射成它在 P1 中出现的下标 pos[v]，
// 再把 P2 的每个值换成 pos[P2[i]]，得到一个下标序列 a[]。
// P1 与 P2 的公共子序列 <-> a[] 的严格上升子序列，
// 所以答案就是 a[] 的 LIS 长度。
//
// LIS 写法：
//   c[j] = 当前所有 lis 值等于 j 的元素中，a 值最小的那个
//   f[i] = 以第 i 个元素结尾的 lis 值
//         = 第一个满足 c[j] > a[i] 的下标 j（a[i] 相等时能接到长度 j 后面，
//           所以要用 >，不能用 >=，对应严格上升）
//   c[f[i]] = min(c[f[i]], a[i])
// c[] 单调不减，所以"第一个大于 a[i] 的位置"用手写二分找，
// 模板来自 rbook《二分查找》文章的 first_true，不调用 upper_bound。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5; //数组的最大长度

int n;        //排列的长度
int a[maxn];  //把 P2 的值换成它在 P1 中的下标之后得到的序列
int pos[maxn];//pos[v] = 值 v 在排列 P1 中的位置
int c[maxn];  //c[j]表示: 所有 lis值 == j 那些元素中, 值最小的那个
int f[maxn];  //f[i] = 第 i 个元素(即 a[i]) 的 lis 值

//手写二分: 在 c[l..r] 中查找第一个满足 c[mid] > x 的位置。
//c[] 单调不减，check(mid) 形如 false false ... false true true ... true。
//区间右端传 n+1，位置 n+1 是虚拟位置(c[n+1] 是哨兵无穷大)，表示"不存在 > x 的元素"。
int first_greater(int l, int r, int x){
    while(l < r){
        int mid = l + (r - l) / 2;
        if(c[mid] > x) r = mid;      //答案在左半边(或就是 mid)
        else l = mid + 1;            //c[mid] <= x, mid 及左边都不可能是答案
    }
    return l;
}

//求 a[1..n] 的 LIS: c 与 f 的含义见上面的注释
void lis(){
    memset(c,0x7f,sizeof(c)); //先全部置成无穷大, 表示还没有 lis值==j 的元素
    //虚拟位置 n+1 也是无穷大, 用它兜底, 保证一定找得到一个 > a[i] 的位置;
    //由于 a[i] <= n < c[n+1], 二分永远不会真的返回 n+1
    f[1] = 1;                 //第一个元素自己就构成长度 1 的上升子序列
    c[1] = a[1];
    for(int i=2;i<=n;++i){
        f[i] = first_greater(1, n+1, a[i]); //a[i] 的 lis值
        c[f[i]] = min(c[f[i]],a[i]);        //lis值相同的元素里, 只保留值最小的
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    //第一行: 排列 P1, 记下每个值在 P1 中出现的位置
    for(int i=1;i<=n;++i){
        int v;
        cin >> v;
        pos[v] = i;
    }
    //第二行: 排列 P2, 把每个值换成它在 P1 中的位置, 得到序列 a
    for(int i=1;i<=n;++i){
        int v;
        cin >> v;
        a[i] = pos[v];
    }

    lis();

    //答案就是整个序列里最大的 lis值
    int ans = 0;
    for(int i=1;i<=n;++i){
        ans = max(ans, f[i]);
    }
    cout << ans << "\n";
    return 0;
}
