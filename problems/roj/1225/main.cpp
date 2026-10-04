/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:57
 * update_at: 2026-10-05 05:58
 */
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

typedef long long ll;

struct Metal {
    ll w;      // 该种金属的总重量
    ll v;      // 该种金属的总价值
    double u;  // 单价 = v / w
};

const int MAXS = 105;
Metal a[MAXS];

bool cmp(Metal x, Metal y) {
    return x.u > y.u;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int k;
    cin >> k;
    while (k--) {
        ll w, s;
        cin >> w >> s;
        for (int i = 1; i <= s; i++) {
            cin >> a[i].w >> a[i].v;
            a[i].u = (double)a[i].v / (double)a[i].w;
        }
        sort(a + 1, a + s + 1, cmp);
        double ans = 0;
        ll rest = w;
        for (int i = 1; i <= s && rest > 0; i++) {
            ll take = min(a[i].w, rest);
            ans += take * a[i].u;
            rest -= take;
        }
        cout << fixed << setprecision(2) << ans << "\n";
    }
    return 0;
}
