/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:33
 * update_at: 2026-10-05 00:33
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int LANDINGS = 10; // 题面固定的落地次数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    double h; // 初始高度，用 double 保存
    cin >> h;

    // 总路程 = 初始下落 h + 前 9 次反弹的往返（第 i 次反弹高度为 h/2^i，往返各一次）
    double total = h;
    double cur = h / 2.0;
    for (int i = 1; i < LANDINGS; i++) {
        total += 2.0 * cur; // 当前曲线的来回各一段
        cur /= 2.0;          // 下一段反弹高度减半
    }

    // 第 10 次反弹的高度
    double h10 = h / (1LL << LANDINGS); // h / 2^10 = h / 1024，用 64 位整数保证精确

    // 输出对齐 C++ cout 默认行为：6 位有效数字、去尾零
    cout << total << "\n" << h10 << "\n";

    return 0;
}