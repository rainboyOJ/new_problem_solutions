/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 06:24
 * update_at: 2026-10-08 06:24
 */
// main.cpp：1816《取石子》。
// 每步从一堆取 a~b 个，取完任意一堆的人立即获胜，无路可走者输。
// 记 M = a+b。先把"一步能取空"的堆单独处理（a<=x_i<=b 时先手立即获胜）；
// 剩下的局面里，把一堆留在 [a,b] 区间等于把胜利送给对手，是自杀着法，
// 可以从着法集合里删掉而不改变胜负。这样化简出的每堆是可独立计算的公平组合游戏，
// Grundy 值按 x_i mod M 的余数 r 分段给出，整体异或和决定胜负。
// 与 main.py 同一算法，单组 O(n)，总 O(sum n)。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;          // 读不到组数直接结束
    while (t--) {
        ll n, a, b;
        cin >> n >> a >> b;
        ll M = a + b;                   // 循环节长度，最大 2e9，必须用 ll
        ll xr = 0;                      // 化简后各堆 Grundy 值的异或和
        bool instant = false;           // 是否存在"一步取空立即获胜"的堆
        for (ll i = 0; i < n; i++) {
            ll x;
            cin >> x;
            if (a <= x && x <= b) {     // 这堆一次取完，先手当场获胜
                instant = true;
                continue;
            }
            if (x < a) continue;        // 取不动，Grundy = 0
            if (x < M) {                // b < x < M：一步可取到 <a 的死区，Grundy = 1
                xr ^= 1;
                continue;
            }
            ll r = x % M;
            if (a == 1) {
                xr ^= r;                // a=1 时余数本身就是 Grundy 值
            } else if (r < a) {
                /* Grundy = 0，什么都不做 */
            } else if (r >= M - a) {
                xr ^= 1;
            } else {
                xr ^= 2 + (r - a) / a;
            }
        }
        cout << ((instant || xr != 0) ? "Alice" : "Bob") << "\n";
    }
    return 0;
}
