/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:47
 */
// brute.cpp：把十进制表示逐字符累加。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string number;
    cin >> number;
    int answer = 0;
    for (int i = 0; i < (int)number.size(); i++) answer += number[i] - '0';
    cout << answer << '\n';
    return 0;
}
