/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 00:41
 * update_at: 2026-10-09 00:41
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// 读入的整数。题面只说「一个整数」，实测数据取值覆盖有符号 32 位全区间
// [-2147483648, 2147483647]（problem10 / problem9），用 ll 读写不会有截断或溢出风险。
ll a;

// 开区间 (1, 100) 判断：a 严格大于 1 且严格小于 100 时输出 yes。
// 不满足条件时什么都不输出，保持 0 字节（连换行也不能多打）。
void solve() {
    if (!(cin >> a)) return; // 无输入时不产生任何输出
    if (a > 1 && a < 100) {
        cout << "yes\n";
    }
}

int main() {
    solve();
    return 0;
}
