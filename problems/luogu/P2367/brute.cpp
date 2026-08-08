#include <bits/stdc++.h>
using namespace std;

int a[10005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, p;
    cin >> n >> p;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= p; i++) {
        int l, r, z;
        cin >> l >> r >> z;
        // 朴素做法：把区间里的每个学生成绩都加上 z。
        for (int j = l; j <= r; j++) {
            a[j] += z;
        }
    }

    int ans = a[1];
    for (int i = 2; i <= n; i++) {
        if (a[i] < ans) ans = a[i];
    }

    cout << ans << '\n';
    return 0;
}
