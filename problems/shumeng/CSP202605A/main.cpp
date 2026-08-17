/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-08-17 22:40
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> normal(n); // 普通四舍五入的结果
    vector<long long> banker(n); // 银行家舍入的结果
    for (int i = 0; i < n; i++) {
        string value;
        cin >> value;
        // 按字符串切分，避免浮点解析误差
        size_t dot = value.find('.');
        long long integer_part = stoll(value.substr(0, dot));
        int decimal_part = value[dot + 1] - '0';

        // 普通四舍五入：小数位 >= 5 进位
        normal[i] = integer_part + (decimal_part >= 5);

        // 银行家舍入：小数位 > 5 进位；等于 5 时向偶数靠拢
        banker[i] = integer_part;
        if (decimal_part > 5 || (decimal_part == 5 && (integer_part & 1))) {
            banker[i]++;
        }
    }

    for (int i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << normal[i];
    }
    cout << '\n';
    for (int i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << banker[i];
    }
    cout << '\n';
    return 0;
}