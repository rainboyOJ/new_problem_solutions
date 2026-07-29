// brute.cpp：小数据暴力解，线性扫描第一个和最后一个等于 target 的位置。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, t;
    cin >> n >> t;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;

    int first = -1, last = -1;
    // 从左到右扫一遍，记录 target 第一次和最后一次出现的位置。
    for (int i = 0; i < n; i++) {
        if (a[i] == t) {
            if (first == -1)
                first = i; // 第一次命中
            last = i;      // 持续更新到最后一次
        }
    }
    cout << first << ' ' << last << '\n';
    return 0;
}
