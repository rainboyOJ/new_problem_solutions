/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 16:24
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string isbn;
    cin >> isbn;

    int sum = 0;
    int digit_count = 0;
    // 只计算前 9 个数字，连字符不参与校验。
    for (int i = 0; i < (int)isbn.size(); i++) {
        if ('0' <= isbn[i] && isbn[i] <= '9') {
            digit_count++;
            if (digit_count <= 9) {
                sum += (isbn[i] - '0') * digit_count;
            }
        }
    }

    int remainder = sum % 11;
    char correct = remainder == 10 ? 'X' : char('0' + remainder);
    if (isbn.back() == correct) {
        cout << "Right\n";
    } else {
        isbn.back() = correct;
        cout << isbn << '\n';
    }

    return 0;
}
