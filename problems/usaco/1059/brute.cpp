/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 13:52
 * update_at: 2026-07-11 13:54
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

long long x[10];      // 输入的 7 个数
long long target[10]; // 排序后的输入多重集合
long long cur[10];    // 某组 A,B,C 生成出的 7 个数

bool same_multiset() {
    for (int i = 0; i < 7; i++) {
        if (cur[i] != target[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < 7; i++) {
        cin >> x[i];
        target[i] = x[i];
    }
    sort(target, target + 7);

    // 暴力枚举三个秘密数字分别等于输入中的哪个值，再检查能否生成同一个多重集合。
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            for (int k = 0; k < 7; k++) {
                long long A = x[i];
                long long B = x[j];
                long long C = x[k];
                if (!(A <= B && B <= C)) {
                    continue;
                }

                cur[0] = A;
                cur[1] = B;
                cur[2] = C;
                cur[3] = A + B;
                cur[4] = A + C;
                cur[5] = B + C;
                cur[6] = A + B + C;
                sort(cur, cur + 7);

                if (same_multiset()) {
                    cout << A << ' ' << B << ' ' << C << '\n';
                    return 0;
                }
            }
        }
    }

    return 0;
}
