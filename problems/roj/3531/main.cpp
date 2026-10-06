/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:11
 * update_at: 2026-10-06 13:11
 */
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 10005;

int n, m;
int a[MAXN]; // 当前排列

// 原地求字典序下一个排列，O(n)
void next_permutation() {
    int i = n - 2;
    while (i >= 0 && a[i] >= a[i + 1]) i--; // 从右找第一个 a[i] < a[i+1]
    if (i < 0) return; // 已是最大排列，题面保证不会出现
    int j = n - 1;
    while (a[j] <= a[i]) j--; // 从右找第一个大于 a[i] 的数
    swap(a[i], a[j]);         // 交换，让第 i 位增大得尽量少
    // 反转降序后缀 a[i+1..n-1] 为升序最小
    int l = i + 1, r = n - 1;
    while (l < r) {
        swap(a[l], a[r]);
        l++;
        r--;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) next_permutation(); // 做 m 次后继
    for (int i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << a[i];
    }
    cout << '\n';
    return 0;
}
