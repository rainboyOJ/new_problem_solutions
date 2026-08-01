/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 09:20
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long b, c, l, r;
    cin >> b >> c >> l >> r;

    long long first = l;
    if (first % 2 != 0) first++;

    long long answer = 0;
    for (long long x = first; x <= r; x += 2) {
        answer += x * x + b * x + c;
    }
    cout << answer * 2 << '\n';

    return 0;
}
