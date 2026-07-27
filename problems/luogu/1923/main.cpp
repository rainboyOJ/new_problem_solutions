/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5000005;

int n, k;
int a[MAXN];

// 快速选择：在 a[l..r] 中找第 k 小的数
int quick_select(int l, int r, int k) {
    if (l == r) return a[l];

    // 选第一个元素作为基准
    int pivot = a[l];
    int i = l, j = r;

    while (i < j) {
        // 从右往左找第一个小于 pivot 的数
        while (i < j && a[j] >= pivot) j--;
        // 从左往右找第一个大于 pivot 的数
        while (i < j && a[i] <= pivot) i++;
        if (i < j) swap(a[i], a[j]);
    }
    // 把基准放到正确位置
    swap(a[l], a[i]);

    // 基准的下标 i 就是第 i-l+1 小
    if (k == i - l + 1) return a[i];
    else if (k < i - l + 1) return quick_select(l, i - 1, k);
    else return quick_select(i + 1, r, k - (i - l + 1));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    k++; // 题目第 0 小对应 C++ 第 1 小
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    cout << quick_select(1, n, k) << "\n";

    return 0;
}
