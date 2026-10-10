/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 01:04
 * update_at: 2026-10-09 01:13
 */
// main.cpp：按行李重量选择单价计费，保留 2 位小数输出。
#include <iomanip>
#include <iostream>

using namespace std;

typedef long long ll;

double weight; // 行李重量（公斤），题面未给上界，实测数据最大 1000.00
double cost;   // 应收费用（元）

bool read_input() {
    return bool(cin >> weight);
}

void solve() {
    // 重量超过 20 公斤时，是【全部重量】都按 1.98 元/公斤计费，
    // 而不是 20 公斤按 1.68 元、超出部分按 1.98 元分段累加。
    if (weight <= 20.0) {
        cost = weight * 1.68;
    } else {
        cost = weight * 1.98;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!read_input()) {
        return 0; // 无输入时不输出，与参考实现 std.cpp 的 scanf 判失败口径一致
    }
    solve();

    cout << fixed << setprecision(2) << cost << "\n";
    return 0;
}
