/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 20:26
 */
// brute.cpp：小数据直接维护每个数，逐项求和并逐项乘法更新。
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 2009731336725594113LL;
const int MOD_SMALL = 2019;

long long unit[5] = {
    314882150829468584LL,
    427197303358170108LL,
    1022292690726729920LL,
    1698479428772363217LL,
    2006101093849356424LL,
};

long long multiply_mod(long long left, long long right) {
    return (long long)((__int128)left * right % MOD);
}

int get_value(long long number) {
    return (int)(number % MOD_SMALL);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, query_count;
    cin >> n >> query_count;
    vector<long long> value(n + 1);
    for (int i = 1; i <= n; i++) value[i] = i;
    while (query_count--) {
        int left, right;
        cin >> left >> right;
        int answer = 0;
        for (int i = left; i <= right; i++) answer += get_value(value[i]);
        cout << answer << '\n';
        int type = answer % 5;
        for (int i = left; i <= right; i++) value[i] = multiply_mod(value[i], unit[type]);
    }

    return 0;
}
