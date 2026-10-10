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
int m1, m2;

// 把 m1 分解质因数，返回各质数及指数
vector<pair<int, int> > factorize(int x) {
    vector<pair<int, int> > res;
    for (int d = 2; d * d <= x; d++) {
        if (x % d == 0) {
            int e = 0;
            while (x % d == 0) { x /= d; e++; }
            res.push_back(make_pair(d, e));
        }
    }
    if (x > 1) res.push_back(make_pair(x, 1));
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m1 >> m2;
    vector<pair<int, int> > fac = factorize(m1);
    int ans = -1;
    for (int i = 0; i < n; i++) {
        int s;
        cin >> s;
        int steps = 0;
        bool ok = true;
        for (size_t fi = 0; fi < fac.size(); fi++) {
            int p = fac[fi].first;
            int e = fac[fi].second * m2;   // 需求指数
            int cnt = 0;
            while (s % p == 0) { s /= p; cnt++; }
            if (cnt == 0) { ok = false; break; }
            int t = (e + cnt - 1) / cnt;
            if (t > steps) steps = t;
        }
        if (ok && (ans < 0 || steps < ans)) ans = steps;
    }
    cout << ans << "\n";
    return 0;
}
