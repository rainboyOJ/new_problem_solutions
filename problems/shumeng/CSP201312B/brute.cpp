/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:45
 */
// brute.cpp：按 ISBN 固定格式逐位取出前 9 个数字，再直接套校验公式。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string isbn;
    cin >> isbn;

    int positions[9] = {0, 2, 3, 4, 6, 7, 8, 9, 10};
    int sum = 0;
    for (int i = 0; i < 9; i++) {
        sum += (isbn[positions[i]] - '0') * (i + 1);
    }

    int remainder = sum % 11;
    char correct = remainder == 10 ? 'X' : char('0' + remainder);
    if (isbn[12] == correct) {
        cout << "Right\n";
    } else {
        isbn[12] = correct;
        cout << isbn << '\n';
    }

    return 0;
}
