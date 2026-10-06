/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:51
 * update_at: 2026-10-06 13:51
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// isbn 保存输入的整个 ISBN 串，形如 0-670-82162-4
string isbn;

int main() {
    cin >> isbn;

    // 前 9 位数字（去掉 '-'）依次乘 1..9 求和，再对 11 取余
    ll weighted_sum = 0;
    ll factor = 1;
    ll len = isbn.size();
    for (ll i = 0; i < len - 1; i++) {
        if (isbn[i] == '-') {
            continue;
        }
        weighted_sum += (isbn[i] - '0') * factor;
        factor++;
    }

    ll remainder = weighted_sum % 11;
    char correct; // 计算出的正确识别码，余 10 时记作 'X'
    if (remainder == 10) {
        correct = 'X';
    } else {
        correct = '0' + remainder;
    }

    if (isbn[len - 1] == correct) {
        cout << "Right" << endl;
    } else {
        // 保留原前缀，替换最后一位识别码
        for (ll i = 0; i < len - 1; i++) {
            cout << isbn[i];
        }
        cout << correct << endl;
    }
    return 0;
}
