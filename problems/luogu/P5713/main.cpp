/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; // 题目数量
    cin >> n;
    // 本地方案：每题 5 分钟
    int local = 5 * n;
    // 洛谷方案：每题 3 分钟 + 额外 11 分钟
    int luogu = 3 * n + 11;
    // 谁总耗时短就输出谁
    if (local < luogu) {
        cout << "Local" << endl;
    } else {
        cout << "Luogu" << endl;
    }
    return 0;
}
