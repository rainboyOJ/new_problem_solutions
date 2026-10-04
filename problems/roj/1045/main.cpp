/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-29 16:02
 * update_at: 2026-09-29 16:02
 */

#include <iostream>
using namespace std;

typedef long long ll;

// 兑换大奖所需的"幸运"瓶盖数与"鼓励"瓶盖数
const ll LUCKY_NEED = 10;
const ll ENCOURAGE_NEED = 20;

int main() {
    // 读入一行两个整数：幸运瓶盖数 a、鼓励瓶盖数 b
    ll a, b;
    if (!(cin >> a >> b)) return 0;

    // 两条兑换路径满足任意一条即可，判定式是"或"
    bool can_reward = (a >= LUCKY_NEED) || (b >= ENCOURAGE_NEED);

    cout << (can_reward ? 1 : 0) << endl;
    return 0;
}