/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:57
 * update_at: 2026-10-05 05:57
 */
// main.cpp：Charley 必须与同行人同速跟随；挑出 t>=0 的人中最早到达终点的时刻。
#include <iostream>

typedef long long ll;

const ll DIST = 4500;                // 赛道长度（米）
const ll NUM = DIST * 36 / 10;        // 16200：4500m / (v km/h) 换算到秒数时除以 v 的值

int main() {
    ll n;
    std::cin >> n;
    while (n != 0) {                  // n = 0 表示输入结束
        ll best = (ll)9e18;            // 本组答案：所有可用同行人到达时刻的最小值
        for (ll i = 0; i < n; i++) {
            ll v, t;
            std::cin >> v >> t;
            if (t < 0) continue;       // 提前出发：Charley 出发时已在前方，追不上，跳过
            ll ride = (NUM + v - 1) / v; // 骑 4500m 需要 ceil(16200 / v) 秒
            ll arrive = t + ride;       // 该同行人独自到达终点的时刻
            if (arrive < best) best = arrive;
        }
        std::cout << best << '\n';
        std::cin >> n;
    }
    return 0;
}