/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:26
 * update_at: 2026-10-05 05:26
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 35;
ll ways[MAXN]; // ways[i] 表示走完 i 级楼梯的走法数

int main() {
    ways[0] = 1; // 边界：一步不走也算一种方案
    ways[1] = 1; // 边界：只能跨 1 级
    for (int i = 2; i < MAXN; i++) {
        ways[i] = ways[i - 1] + ways[i - 2]; // 按最后一步跨 1 级或 2 级分类
    }

    ll n;
    while (cin >> n) {
        cout << ways[n] << "\n";
    }
    return 0;
}
