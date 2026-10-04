/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:40
 * update_at: 2026-10-05 00:40
 */
#include <iostream>
using namespace std;

typedef long long ll;

ll n;
int digit[12]; // 低位在前存放各位数字
int cnt;       // n 的位数

// 反复取 n % 10 得到最低位，再用 n / 10 把最低位去掉，直到 n 变为 0
void digits_from_low() {
    while (n) {
        digit[++cnt] = n % 10;
        n /= 10;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    digits_from_low();

    for (int i = 1; i <= cnt; ++i) {
        if (i > 1) cout << ' ';
        cout << digit[i];
    }
    cout << '\n';
    return 0;
}
