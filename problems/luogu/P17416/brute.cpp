/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-06 19:06
 * update_at: 2026-09-06 19:22
 */
// brute.cpp：小数据暴力解，枚举长度为 k 的选择序列，用来辅助对拍。
#include <bits/stdc++.h>
using namespace std;
int n, k;
int a[20];
int chosen[20];
long long answer = 0;

void dfs(int pos, int count) {
    if (count == k) {
        int maximum = 0;
        for (int i = 0; i < k; i++) {
            maximum = max(maximum, chosen[i]);
        }
        long long value = 0;
        for (int i = 0; i < k; i++) {
            value += (chosen[i] ^ maximum);
        }
        answer = max(answer, value);
        return;
    }
    if (n - pos < k - count) {
        return;
    }
    for (int i = pos; i < n; i++) {
        chosen[count] = a[i];
        dfs(i + 1, count + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    dfs(0, 0);
    cout << answer << '\n';
    return 0;
}
