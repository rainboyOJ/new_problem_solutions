#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;

int n;
long long a[MAXN]; // 待排序数组

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    sort(a + 1, a + n + 1);

    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';
    return 0;
}
