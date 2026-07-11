/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 14:45
 * update_at: 2026-07-11 14:46
 */
#include <bits/stdc++.h>
using namespace std;

const int COW_CNT = 8;
const int MAXN = 10;

int n;
string order_cow[COW_CNT] = {
    "Beatrice",
    "Belinda",
    "Bella",
    "Bessie",
    "Betsy",
    "Blue",
    "Buttercup",
    "Sue"
};

string need_a[MAXN], need_b[MAXN]; // need_a[i] 必须和 need_b[i] 相邻

int find_pos(string name) {
    for (int i = 0; i < COW_CNT; i++) {
        if (order_cow[i] == name) {
            return i;
        }
    }
    return -1;
}

bool check_order() {
    for (int i = 1; i <= n; i++) {
        int pos_a = find_pos(need_a[i]);
        int pos_b = find_pos(need_b[i]);
        if (abs(pos_a - pos_b) != 1) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        string t;
        cin >> need_a[i] >> t >> t >> t >> t >> need_b[i];
    }

    // order_cow 初始就是字典序。按字典序枚举排列，第一个合法排列就是答案。
    do {
        if (check_order()) {
            for (int i = 0; i < COW_CNT; i++) {
                cout << order_cow[i] << '\n';
            }
            return 0;
        }
    } while (next_permutation(order_cow, order_cow + COW_CNT));

    return 0;
}
