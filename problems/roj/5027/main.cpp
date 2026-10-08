/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 16:12
 * update_at: 2026-10-08 16:13
 */
// main.cpp：本题无输入，直接从小到大枚举满足全部同余条件的最少人数。
#include <iostream>

typedef long long ll;

int main() {
    // 人数必须是 7 的倍数，所以从 7 开始每次加 7 枚举；
    // 首个同时满足「每行 2..6 人都恰好多出 1 人」的 n 就是最少人数。
    for (ll n = 7; ; n += 7) {
        if (n % 2 == 1 && n % 3 == 1 && n % 4 == 1 && n % 5 == 1 && n % 6 == 1) {
            std::cout << n << "\n";
            return 0;
        }
    }
    return 0; // 不会到达
}
