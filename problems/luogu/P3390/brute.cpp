// brute.cpp：小数据暴力解，直接把矩阵连乘 k 次。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;
const long long MOD = 1000000007LL;

int n;
long long k;

struct Matrix {
    long long a[MAXN][MAXN];
};

Matrix multiply_matrix(const Matrix &x, const Matrix &y) {
    Matrix z;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            z.a[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int t = 1; t <= n; t++) {
            for (int j = 1; j <= n; j++) {
                z.a[i][j] = (z.a[i][j] + x.a[i][t] * y.a[t][j]) % MOD;
            }
        }
    }
    return z;
}

Matrix identity_matrix() {
    Matrix res;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            res.a[i][j] = (i == j ? 1 : 0);
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    Matrix base;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            long long x;
            cin >> x;
            x %= MOD;
            if (x < 0) x += MOD;
            base.a[i][j] = x;
        }
    }

    Matrix ans = identity_matrix();
    for (long long step = 1; step <= k; step++) {
        ans = multiply_matrix(ans, base);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j > 1) cout << ' ';
            cout << ans.a[i][j];
        }
        cout << "\n";
    }

    return 0;
}
