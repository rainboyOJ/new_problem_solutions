/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:45
 * update_at: 2026-11-10 23:45
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 记录导弹到两个拦截系统的距离平方
struct Missile {
    long long d1;
    long long d2;

    bool operator<(const Missile& other) const {
        return d1 < other.d1; // 按到系统 1 的距离升序排序
    }
};

const int MAXN = 100005;
Missile a[MAXN];
long long suf_max[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long x1, y1, x2, y2;
    if (!(cin >> x1 >> y1 >> x2 >> y2)) return 0;

    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        long long x, y;
        cin >> x >> y;
        a[i].d1 = (x - x1) * (x - x1) + (y - y1) * (y - y1);
        a[i].d2 = (x - x2) * (x - x2) + (y - y2) * (y - y2);
    }

    sort(a + 1, a + n + 1);

    // 预处理 d2 的后缀最大值
    suf_max[n + 1] = 0;
    for (int i = n; i >= 1; --i) {
        suf_max[i] = max(suf_max[i + 1], a[i].d2);
    }

    // 枚举系统 1 覆盖前 k 个点 (k=0 到 n)
    long long ans = suf_max[1]; // k = 0 时全由系统 2 覆盖
    for (int k = 1; k <= n; ++k) {
        long long cost = a[k].d1 + suf_max[k + 1];
        ans = min(ans, cost);
    }

    cout << ans << "\n";

    return 0;
}
