#include <bits/stdc++.h>
using namespace std;

// brute.cpp：每个询问复制区间并排序，只适合小数据验证。

const int MAXN = 505;

int n, m;
int a[MAXN];
int temp[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        int len = 0;
        for (int j = l; j <= r; j++) {
            len++;
            temp[len] = a[j];
        }
        sort(temp + 1, temp + len + 1);
        cout << temp[k] << '\n';
    }

    return 0;
}
