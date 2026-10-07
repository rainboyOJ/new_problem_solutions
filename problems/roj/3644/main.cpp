/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:50
 * update_at: 2026-10-06 15:50
 */
#include <iostream>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll a, b, c;
    cin >> a >> b >> c;
    // 权重整体乘 100 化为整数 2/3/5，分母统一为 10；
    // 数据保证 A,B,C 是 10 的倍数，分子必被 10 整除，整除即得整数总评
    cout << (a * 2 + b * 3 + c * 5) / 10 << "\n";
    return 0;
}
