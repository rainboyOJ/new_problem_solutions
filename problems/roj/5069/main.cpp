/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 02:01
 * update_at: 2026-10-09 02:01
 */
// 一本通 2068《【例2.6】鸡兔同笼》
// 题面三步判据（关键词 / 括号内算法名 / 标题）全空 ⇒ 未指定实现手段，直接用代数公式。
// 设鸡 c 只、兔 r 只：c + r = x，2c + 4r = y ⇒ c = (4x - y) / 2，r = (y - 2x) / 2。
// 【输出顺序】鸡在前、兔在后，由数据判定：
//   p1 (1 2) -> "1 0"、p2 (1 4) -> "0 1"，两点即可判别顺序（0 是合法输出）。
// 数据实测：10 个点全部满足 2x <= y <= 4x 且 y 为偶数，两个分子都是非负偶数，整除无歧义；
// 无解输入（y 为奇 / y < 2x / y > 4x）题面未定义，故不加特判、按公式直算。
// 范围：数据最大 x = y/2 = 10^6 ⇒ 中间量 4x <= 4 * 10^6 << 2^31 - 1；
// 仍按规范统一用 ll，避免任何隐含的 32 位假设。
#include <iostream>

using namespace std;

typedef long long ll;

ll x; // 头的数量
ll y; // 脚的数量

// 由方程组解出鸡、兔数量并按「鸡 兔」顺序输出。
void solve() {
    ll chicken = (4 * x - y) / 2; // 鸡：每只 2 只脚
    ll rabbit = (y - 2 * x) / 2;  // 兔：每只 4 只脚
    cout << chicken << " " << rabbit << "\n";
}

int main() {
    if (!(cin >> x >> y)) return 0; // 无输入 / 非法 token：静默退出
    solve();
    return 0;
}
