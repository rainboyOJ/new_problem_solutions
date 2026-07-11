/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 13:52
 * update_at: 2026-07-11 13:54
 */
#include <bits/stdc++.h>
using namespace std;

long long a[10]; // 输入的 7 个数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < 7; i++) {
        cin >> a[i];
    }

    sort(a, a + 7);

    long long A = a[0];
    long long B = a[1];
    long long C = a[6] - A - B;

    cout << A << ' ' << B << ' ' << C << '\n';

    return 0;
}
