/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 22:55
 * update_at: 2026-10-08 22:55
 */
#include <iostream>

using namespace std;

typedef long long ll;

const ll MAXN = 25; // 题面 n <= 20，多开几个留余量

ll n;         // 待排序数的个数，题面给定 1 <= n <= 20
ll a[MAXN];   // a[0..n-1] 存放输入的非负整数

// 冒泡排序（降序）：题面显式要求「冒泡排序」，因此不调用 std::sort
void bubble_sort() {
    for (ll i = 0; i < n - 1; i++) {        // 外层控制趟数
        for (ll j = 0; j < n - 1 - i; j++) { // 每趟结束，末尾 i 个数已就位，内层范围收缩
            if (a[j] < a[j + 1]) {           // 降序：前一个数比后一个小就交换
                ll temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

void solve() {
    if (!(cin >> n)) return;

    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    bubble_sort();

    for (ll i = 0; i < n; i++) {
        cout << a[i] << "\n"; // 题面要求每个数占一行
    }
}

int main() {
    solve();
    return 0;
}
