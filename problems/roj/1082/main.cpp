/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:27
 * update_at: 2026-10-05 00:27
 */
#include <iostream>
using namespace std;

typedef long long ll;

ll a, b, n; // 输入：分数 a/b 的小数点后第 n 位

int main() {
    cin >> a >> b >> n;
    // 模拟长除法：每轮把余数乘 10 再对 b 取商，商就是这一位小数
    ll remainder = a; // 当前余数，初始为分子 a
    ll digit = 0;     // 第 n 位小数的数字
    for (ll i = 1; i <= n; i++) {
        remainder = remainder * 10;
        digit = remainder / b;
        remainder = remainder % b;
    }
    cout << digit << endl;
    return 0;
}
