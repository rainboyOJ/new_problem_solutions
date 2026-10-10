/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n;
ll a[205];             // marks 复制一倍
ll f[205][205];

ll best_energy() {
    int size = 2 * n;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            f[i][j] = 0;
    for (int length = 2; length <= n; length++) {
        for (int i = 0; i < size - length; i++) {
            int j = i + length - 1;
            ll head = a[i], tail = a[j + 1];
            for (int k = i; k < j; k++) {
                ll energy = f[i][k] + f[k + 1][j] + head * a[k + 1] * tail;
                if (energy > f[i][j]) f[i][j] = energy;
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i < n; i++)
        if (f[i][i + n - 1] > ans) ans = f[i][i + n - 1];
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i + n] = a[i];
    }
    cout << best_energy() << "\n";
    return 0;
}
