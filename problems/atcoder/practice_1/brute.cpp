/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-09 17:55
 * update_at: 2026-07-09 17:55
 */
// brute.cpp：这题没有需要优化的算法，朴素做法就是按题意读入并输出。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, c;
    string s;
    cin >> a >> b >> c >> s;
    cout << a + b + c << ' ' << s << '\n';

    return 0;
}
