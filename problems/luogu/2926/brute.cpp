/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-19 11:59
 * update_at: 2026-07-19 11:59
 */
#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据朴素解，直接检查每一对牛是否满足整除关系。

const int MAXN = 105;

int n;
int value[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> value[i];

    for (int i = 1; i <= n; i++) {
        int answer = 0;
        for (int j = 1; j <= n; j++) {
            if (i != j && value[i] % value[j] == 0) answer++;
        }
        cout << answer << '\n';
    }
    return 0;
}
