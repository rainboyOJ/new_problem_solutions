/*
 * Author by Rainboy blog: https://rainboylv.com github:
 * https://github.com/rainboylvx rbook: -> https://rbook.roj.ac.cn
 * https://rbook2.roj.ac.cn rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-19 18:44
 * update_at: 2026-09-19 18:44
 */
// main2.cpp：两个排列的最长公共子序列（只维护 tail 的写法）。
//
// 建模：把 P1 的每个值映射成它在 P1 中的下标 pos[v]，
// 再把 P2 的每个值换成 pos[P2[i]]，得到一个下标序列 a[]。
// P1 与 P2 的公共子序列 <-> a[] 的严格上升子序列，
// 所以答案就是 a[] 的 LIS 长度。
//
// LIS 写法：
//   tail[len] = 长度为 len 的严格上升子序列中，末尾元素的最小可能值
//   对每个 x，二分找 tail 中第一个 >= x 的位置 p：
//     - 找到：tail[p] = x（让长度为 p 的子序列结尾更小）
//     - 找不到（p 落在虚拟位置 len+1）：长度加一后追加
// 二分是手写的，来自 rbook《二分查找》文章的 first_true 模板，
// 不调用 lower_bound。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
int pos[MAXN];  // pos[v] = 值 v 在排列 P1 中的下标（1-based）
int tail[MAXN]; // tail[len] = 长度为 len 的上升子序列中，末尾下标的最小值
int len;        // tail 的有效长度，也是当前的 LIS 长度

// 在 tail[l..r] 中查找第一个满足 tail[mid] >= x 的位置。
// tail[1..len] 单调不减，check(mid) 形如 false false ... false true true ... true。
// 区间取 [1, len+1]，位置 len+1 是虚拟位置，表示“不存在 >= x 的元素”。
int first_true(int l, int r, int x) {
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (tail[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return l;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        int v;
        cin >> v;
        pos[v] = i;  // 记下每个值在 P1 中的位置
    }

    for (int i = 1; i <= n; i++) {
        int v;
        cin >> v;
        int x = pos[v];  // 把 P2 中的值换成它在 P1 中的位置

        // p 是 tail[1..len] 中第一个 >= x 的位置；找不到就是虚拟位置 len+1
        int p = first_true(1, len + 1, x);

        if (p == len + 1) {  // 没找到说明 x 能接在最长的后面，长度加一
            len++;
            tail[len] = x;
        } else {
            tail[p] = x;  // 找到就替换（让该长度的结尾尽量小）
        }
    }

    cout << len << "\n";

    return 0;
}
