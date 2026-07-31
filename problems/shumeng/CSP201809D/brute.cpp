/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:59
 */
// brute.cpp：小数据暴力解，按字典序递归枚举每个下一天价格允许的三种原价。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 305;
const int MAX_VALUE = 305;

int n;
int second_price[MAXN], first_price[MAXN];

bool dfs(int position) {
    if (position == n) {
        return (first_price[n - 1] + first_price[n]) / 2 == second_price[n];
    }
    int lower = 3 * second_price[position] - first_price[position - 1] - first_price[position];
    for (int next = lower; next <= lower + 2; next++) {
        if (next < 1 || next >= MAX_VALUE) {
            continue;
        }
        first_price[position + 1] = next;
        if (dfs(position + 1)) {
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> second_price[i];
    }

    bool found = false;
    for (int first = 1; first < MAX_VALUE && !found; first++) {
        for (int second = 1; second < MAX_VALUE; second++) {
            if ((first + second) / 2 != second_price[1]) {
                continue;
            }
            first_price[1] = first;
            first_price[2] = second;
            if (n == 2 ? (first + second) / 2 == second_price[2] : dfs(2)) {
                found = true;
                break;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << first_price[i];
    }
    cout << '\n';

    return 0;
}
