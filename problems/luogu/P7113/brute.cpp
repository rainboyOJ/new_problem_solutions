// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;

struct Fraction {
    long long num, den;

    Fraction(long long numerator = 0, long long denominator = 1) {
        num = numerator;
        den = denominator;
        normalize();
    }

    void normalize() {
        if (den < 0) {
            num = -num;
            den = -den;
        }
        long long g = std::gcd(llabs(num), llabs(den));
        if (g != 0) {
            num /= g;
            den /= g;
        }
    }
};

Fraction operator+(const Fraction &a, const Fraction &b) {
    __int128 numerator = (__int128) a.num * b.den + (__int128) b.num * a.den;
    __int128 denominator = (__int128) a.den * b.den;
    return Fraction((long long) numerator, (long long) denominator);
}

Fraction operator/(const Fraction &a, long long x) {
    return Fraction(a.num, a.den * x);
}

int n, m;
vector<int> graph[MAXN];
int outdeg[MAXN];
Fraction ans[MAXN]; // ans[i] : 最终流到汇点 i 的污水量

// 直接按题意递归分流。
void dfs(int u, Fraction cur) {
    if (outdeg[u] == 0) {
        ans[u] = ans[u] + cur;
        return;
    }

    Fraction each = cur / outdeg[u];
    for (int v : graph[u]) {
        dfs(v, each);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        graph[i].clear();
        ans[i] = Fraction(0, 1);

        int d;
        cin >> d;
        outdeg[i] = d;
        for (int j = 1; j <= d; j++) {
            int v;
            cin >> v;
            graph[i].push_back(v);
        }
    }

    for (int i = 1; i <= m; i++) {
        dfs(i, Fraction(1, 1));
    }

    for (int i = 1; i <= n; i++) {
        if (outdeg[i] == 0) {
            cout << ans[i].num << ' ' << ans[i].den << '\n';
        }
    }

    return 0;
}
