#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
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
            if (x.a[i][t] == 0) continue;
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

Matrix matrix_power(Matrix base, long long exp) {
    Matrix res = identity_matrix();

    // 和普通快速幂一样，按指数的二进制位决定是否乘当前底数。
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = multiply_matrix(res, base);
        }
        base = multiply_matrix(base, base);
        exp /= 2;
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

    Matrix ans = matrix_power(base, k);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j > 1) cout << ' ';
            cout << ans.a[i][j];
        }
        cout << "\n";
    }

    return 0;
}
