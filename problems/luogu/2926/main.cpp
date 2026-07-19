/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-19 11:59
 * update_at: 2026-07-19 14:31
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXV = 1000005;

int n;
int value[MAXN];
int frequency[MAXV];
int divisor_cow_count[MAXV];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    int maximum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> value[i];
        frequency[value[i]]++;
        if (maximum < value[i]) maximum = value[i];
    }

    // 数值 d 的每头牛，都会被数值为 d,2d,3d,... 的牛拍到。
    for (int divisor = 1; divisor <= maximum; divisor++) {
        if (frequency[divisor] == 0) continue;
        for (int multiple = divisor; multiple <= maximum; multiple += divisor) {
            divisor_cow_count[multiple] += frequency[divisor];
        }
    }

    for (int i = 1; i <= n; i++) {
        // 统计中包含当前牛自己，题目要求只拍其它牛。
        cout << divisor_cow_count[value[i]] - 1 << '\n';
    }
    return 0;
}
