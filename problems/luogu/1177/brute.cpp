// brute.cpp：小数据暴力解，用选择排序帮助理解排序目标并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n;
long long a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        int best = i;
        for (int j = i + 1; j <= n; j++) {
            if (a[j] < a[best]) {
                best = j;
            }
        }
        swap(a[i], a[best]);
    }

    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';
    return 0;
}
