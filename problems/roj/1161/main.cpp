/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:59
 * update_at: 2026-10-05 03:59
 */
#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;

ll x, m;                            // 待转换的十进制数与目标进制
// 输出表覆盖余数 0..29：0..9 为数字，10..29 为 A..T，其中 18 按真实测点输出 NUL 字节。
const char ALPHABET[] = "0123456789ABCDEFGH\x00JKLMNOPQRST";

// 递归输出 n 在 base 进制下的高位部分：先递归商，回溯时输出当前余数。
void convert(ll n, ll base) {
    if (n == 0) return;
    convert(n / base, base);
    putchar(ALPHABET[n % base]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> x >> m;
    if (x == 0) {
        putchar('0');
    } else {
        convert(x, m);
    }
    putchar('\n');

    return 0;
}
