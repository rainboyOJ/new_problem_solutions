/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:42
 * update_at: 2026-10-06 13:42
 */
#include <iostream>
using namespace std;
typedef long long ll;

// 守望者的逃离：每秒在跑步、休息、闪烁中选一个，求最短逃离时间或最远距离。
int main() {
    ll M, S, T;
    cin >> M >> S >> T;

    ll magic = M;      // 当前魔法值
    ll run_dist = 0;   // 一直跑步的累计距离，同时用来保存当前最优距离
    ll flash_dist = 0; // 按"魔法够就闪、不够就休息"这条路线走的累计距离

    for (ll t = 1; t <= T; t++) {
        run_dist += 17; // 这一秒用来跑步
        if (magic >= 10) {
            magic -= 10; // 这一秒用来闪烁
            flash_dist += 60;
        } else {
            magic += 4; // 魔法不够，这一秒休息攒魔法
        }
        if (flash_dist > run_dist) {
            run_dist = flash_dist; // 闪烁路线更远，切换到该路线
        }
        if (run_dist >= S) {
            cout << "Yes\n" << t << "\n"; // 当前秒数即最短逃离时间
            return 0;
        }
    }

    cout << "No\n" << run_dist << "\n"; // T 秒内都逃不出，输出最远距离
    return 0;
}
