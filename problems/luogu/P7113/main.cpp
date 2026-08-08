#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

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
int indeg[MAXN];
int outdeg[MAXN];
Fraction water[MAXN]; // water[i] : 当前流到结点 i 的总污水量

void read_input() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        graph[i].clear();
        indeg[i] = 0;
        outdeg[i] = 0;
        water[i] = Fraction(0, 1);
    }

    for (int i = 1; i <= n; i++) {
        int d;
        cin >> d;
        outdeg[i] = d;
        for (int j = 1; j <= d; j++) {
            int v;
            cin >> v;
            graph[i].push_back(v);
            indeg[v]++;
        }
    }

    for (int i = 1; i <= m; i++) {
        water[i] = Fraction(1, 1);
    }
}

void solve() {
    queue<int> q;
    int deg[MAXN];
    memcpy(deg, indeg, sizeof(indeg));

    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (outdeg[u] > 0) {
            Fraction each = water[u] / outdeg[u];
            for (int v : graph[u]) {
                water[v] = water[v] + each;
                deg[v]--;
                if (deg[v] == 0) {
                    q.push(v);
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    for (int i = 1; i <= n; i++) {
        if (outdeg[i] == 0) {
            cout << water[i].num << ' ' << water[i].den << '\n';
        }
    }

    return 0;
}
