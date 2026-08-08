#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;

int n;
int a[MAXN];

// check(k)：判断当前的 k 是否能让所有奶牛落到不同的厩里。
bool check(int k) {
    vector<int> used(k, 0);

    for (int i = 1; i <= n; i++) {
        int r = a[i] % k;
        if (used[r]) {
            return false;
        }
        used[r] = 1;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int mn = a[1], mx = a[1];
    for (int i = 2; i <= n; i++) {
        mn = min(mn, a[i]);
        mx = max(mx, a[i]);
    }

    // brute.cpp：直接从 n 开始枚举 K，并暴力检查余数是否冲突。
    // 这个做法最坏是 O((max-min) * n)，只适合小数据和对拍。
    for (int k = n; k <= mx - mn + 1; k++) {
        if (check(k)) {
            cout << k << '\n';
            return 0;
        }
    }

    return 0;
}
