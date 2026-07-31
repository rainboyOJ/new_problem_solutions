/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:20
 */
// brute.cpp：小数据暴力解，统计每条记录之前相同编号的出现次数。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> records(n);
    for (int i = 0; i < n; i++) {
        cin >> records[i];
    }
    for (int i = 0; i < n; i++) {
        int occurrence = 0;
        for (int j = 0; j <= i; j++) {
            if (records[i] == records[j]) {
                occurrence++;
            }
        }
        if (i > 0) {
            cout << ' ';
        }
        cout << occurrence;
    }
    cout << '\n';
    return 0;
}
