/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 23:17
 * update_at: 2026-10-08 23:17
 */
#include <iostream>
using namespace std;

typedef long long ll;

// 稀疏矩阵转简记形式：按行优先在线读取，读到非 0 元素立刻输出「行号 列号 值」。
// 不落地二维数组，额外空间 O(1)；全 0 矩阵自然一条也不输出（0 字节，而非空行）。
void solve() {
    ll n, m;
    if (!(cin >> n >> m)) {
        return; // 无输入时安全退出
    }
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= m; j++) {
            ll v;
            if (!(cin >> v)) {
                return; // 输入不完整时安全退出，避免用上一次的残留值误输出
            }
            if (v != 0) {
                cout << i << " " << j << " " << v << "\n"; // 行列号均从 1 开始
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}
