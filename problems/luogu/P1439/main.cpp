/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-19 18:44
 * update_at: 2026-09-19 18:44
 */
// main.cpp：两个排列的最长公共子序列。
// 把 P1 的每个值映射成它在 P1 中出现的下标，P2 就变成一串下标；
// 公共子序列 <-> P2 中下标严格上升的子序列，于是转化为求这个下标序列的 LIS。
// LIS 用 rbook 模板 lis-binary 的 tail 数组：每个 x 找到 tail 中第一个 >= x 的位置。
// 这里的二分是手写的，来自 rbook《二分查找》文章的 first_true 模板，不调用 lower_bound。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
int pos[MAXN];  // pos[v] = 值 v 在排列 P1 中的下标（1-based）
int tail[MAXN]; // tail[len-1] = 长度为 len 的上升子序列中，末尾下标的最小值
int len;        // tail 的有效长度，也是当前的 LIS 长度

// 在 tail[0..len-1] 中查找第一个满足 check 的位置。
// tail 单调不减，check(p) 形如 false false ... false true true ... true，
// 区间取 [0, len]，位置 len 是虚拟位置，表示"不存在满足条件的元素"。
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

        // p 是 tail 中第一个 >= x 的位置；找不到就是虚拟位置 len
        int p = first_true(0, len, x);

        tail[p] = x;          // 找到就替换（让该长度的结尾尽量小）
        if (p == len) len++;  // 没找到说明 x 能接在最长的后面，长度加一
    }

    cout << len << "\n";

    return 0;
}
