// brute.cpp：小数据暴力解，线性扫描找到第一个 >= target 的位置。
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
    int pos = n;
    for (int i = 0; i < n; i++) {
        if (a[i] >= t) {
            pos = i;
            break;
        }
    }
    cout << pos << '\n';
    return 0;
}
