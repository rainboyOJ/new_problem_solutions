#include <bits/stdc++.h>
using namespace std;

// brute.cpp：直接模拟相邻交换与冒泡排序轮数。
// 只适合小数据，用来帮助理解“每做一轮冒泡排序会发生什么”。

int count_inversion(const vector<int> &a) {
    int n = (int) a.size();
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] > a[j]) {
                ans++;
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x;
            cin >> x;
            --x;
            swap(a[x], a[x + 1]);
        } else {
            int k;
            cin >> k;
            vector<int> b = a;
            int limit = min(k, n);

            for (int round = 0; round < limit; round++) {
                for (int i = 0; i + 1 < n; i++) {
                    if (b[i] > b[i + 1]) {
                        swap(b[i], b[i + 1]);
                    }
                }
            }

            cout << count_inversion(b) << '\n';
        }
    }

    return 0;
}
