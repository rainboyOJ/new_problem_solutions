/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-17 01:40
 * update_at: 2026-10-18 19:44
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string number;    // 原整数 n，最多 30 位，按字符串读
ll rule_count;    // 变换规则条数

// reachable[d] 是位掩码：第 b 位为 1 表示数字 d 能变成数字 b
ll reachable[10];

// 答案最大约 10^30，超过 long long，用 __int128 保存并自己输出
void print_i128(__int128 value) {
    if (value == 0) {
        cout << 0 << '\n';
        return;
    }

    string digits;
    while (value > 0) {
        char ch = '0' + value % 10;
        digits.push_back(ch);
        value /= 10;
    }
    reverse(digits.begin(), digits.end());
    cout << digits << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> number >> rule_count;

    // 每个数字至少能变成自己
    for (int digit = 0; digit < 10; digit++) {
        reachable[digit] = 1LL << digit;
    }

    for (ll i = 0; i < rule_count; i++) {
        ll source, target;
        cin >> source >> target;
        reachable[source] |= 1LL << target; // 走一步
    }

    // Floyd 传递闭包：中转数字 middle 必须在最外层
    for (int middle = 0; middle < 10; middle++) {
        ll middle_bit = 1LL << middle;
        for (int start = 0; start < 10; start++) {
            // start 能变成 middle，就把 middle 能变成的数字一并并入
            if (reachable[start] & middle_bit) {
                reachable[start] |= reachable[middle];
            }
        }
    }

    // 各数位互不影响，按乘法原理把每位可取的数字种数相乘
    __int128 answer = 1;
    for (char ch : number) {
        int digit = ch - '0';
        int kinds = __builtin_popcountll(reachable[digit]);
        answer *= kinds;
    }

    print_i128(answer);
    return 0;
}
