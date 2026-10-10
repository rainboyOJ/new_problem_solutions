/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 07:45
 * update_at: 2026-10-08 07:45
 */
// 一本通 2127《【例1.2】高精度加法》：两个不超过 100 位的非负整数求和。
// 做法：字符串读入 -> 倒序展开成数字（下标 0 是个位，天然按个位对齐）
//       -> 逐位相加并传递进位 -> 处理最高位进位 -> 倒序输出。
// 位数上限 100，加上最高位进位共 101 位，数组开到 105 留余量。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXLEN = 105;  // 位数上限 100 + 最高位进位 1 + 余量
int a[MAXLEN];           // a[i] = 第一个加数第 i 位（权重 10^i），全局默认 0 使不等长自动对齐
int b[MAXLEN];           // b[i] = 第二个加数第 i 位
int c[MAXLEN];           // c[i] = 和的第 i 位

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s1, s2;
    if (!(cin >> s1 >> s2)) return 0;  // 按 token 读入，可容忍行尾空白

    int len1 = s1.length();
    int len2 = s2.length();
    // 倒序展开：最低位落在下标 0，两个加数即使位数不同也自动按个位对齐
    for (int i = 0; i < len1; i++) a[i] = s1[len1 - 1 - i] - '0';
    for (int i = 0; i < len2; i++) b[i] = s2[len2 - 1 - i] - '0';

    int len = max(len1, len2);
    int carry = 0;  // 进位，每一位上只可能是 0 或 1
    for (int i = 0; i < len; i++) {
        int sum = a[i] + b[i] + carry;  // 短的那边高位是 0，不需要额外判断
        c[i] = sum % 10;                // 本位保留个位
        carry = sum / 10;               // 进位交给下一位
    }
    if (carry > 0) c[len++] = carry;    // 最高位进位，如 99 + 1 = 100

    // 去掉前导零（输入带前导零时会出现），结果至少保留一位，故 0 + 0 输出单个 0
    while (len > 1 && c[len - 1] == 0) len--;
    for (int i = len - 1; i >= 0; i--) cout << c[i];
    cout << '\n';
    return 0;
}
