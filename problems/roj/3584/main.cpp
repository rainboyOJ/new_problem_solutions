/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:34
 * update_at: 2026-10-06 14:34
 */
#include <iostream>
using namespace std;

typedef long long ll;

ll n; // 输入的整数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;

    // 按绝对值逐位取末位拼成反转后的数
    ll m = n < 0 ? -n : n; // 去掉符号处理
    ll r = 0;
    while (m > 0) {
        r = r * 10 + m % 10;
        m /= 10;
    }

    // 原数为 0 时循环不执行，r 保持 0，正好符合输出
    cout << (n < 0 ? -r : r) << '\n';
    return 0;
}
