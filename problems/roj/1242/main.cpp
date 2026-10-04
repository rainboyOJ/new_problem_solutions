/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:30
 * update_at: 2026-10-05 06:30
 */
#include <iostream>
#include <iomanip>
using namespace std;

typedef long long ll; // 题目数值默认 ll

const ll CM = 100; // 1 米 = 100 厘米：把精确到厘米的浮点长度放大为整数

const ll MAXN = 10005;
ll a[MAXN]; // a[i]：第 i 条网线长度对应的厘米整数
ll n, k;

// 判断按长度 L 厘米切割，能否得到不少于 k 条网线
bool check(ll L) {
    ll cnt = 0;
    for (ll i = 1; i <= n; ++i) {
        cnt += a[i] / L;
        if (cnt >= k) return true; // 提前满足可剪枝
    }
    return cnt >= k;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    ll max_a = 0;
    for (ll i = 1; i <= n; ++i) {
        double x;
        cin >> x;
        a[i] = (ll)(x * CM + 0.5); // 四舍五入，避免 8.02 * 100 = 801.99... 的浮点误差
        if (a[i] > max_a) max_a = a[i];
    }

    // 二分最大可行长度（厘米整数）
    // lo 始终可行：初值 0 表示“切不出 1 厘米”的哨兵，对应题面无解输出 0.00
    // hi 始终不可行：max_a + 1 比最长网线还长，必然一段都切不出
    ll lo = 0, hi = max_a + 1;
    while (lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        if (check(mid)) lo = mid;
        else hi = mid;
    }

    cout << fixed << setprecision(2) << (double)lo / CM << "\n";
    return 0;
}
