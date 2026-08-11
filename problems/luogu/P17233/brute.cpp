/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-11 07:37
 * update_at: 2026-08-11 11:18
 */
// brute.cpp：小数据暴力解，直接维护当前剩余序列并逐轮扫描。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

int n;
int is_cube[MAXN]; // is_cube[i] 表示 i 是否为完全立方数

void init_cube() {
    // 预处理完全立方数位置，之后每轮扫描时 O(1) 判断当前位置是否要删除。
    for (int i = 1; 1LL * i * i * i < MAXN; i++) {
        is_cube[i * i * i] = 1;
    }
}

int count_deleted(int len) {
    // 当前长度为 len 时，本轮会删除 1^3, 2^3, ... 这些排名。
    int cnt = 0;
    for (int i = 1; 1LL * i * i * i <= len; i++) cnt++;
    return cnt;
}

int count_rounds(int len) {
    // 题目要求先输出总轮数。这里只模拟长度变化，不关心具体元素。
    int rounds = 0;
    while (len > 0) {
        len -= count_deleted(len);
        rounds++;
    }
    return rounds;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init_cube();

    cin >> n;
    vector<int> cur(n);
    for (int i = 0; i < n; i++) cin >> cur[i];

    cout << count_rounds(n) << '\n';

    // cur 表示本轮开始时的当前序列，next_cur 表示删完本轮后的剩余序列。
    vector<int> next_cur;
    while (!cur.empty()) {
        next_cur.clear();

        bool first_output = true;
        for (int i = 0; i < (int)cur.size(); i++) {
            int pos = i + 1;
            if (is_cube[pos]) {
                // 删除位置全部按本轮开始时的 cur 下标判断，符合“同时删除”。
                if (!first_output) cout << ' ';
                cout << cur[i];
                first_output = false;
            }
            else {
                // 没被删除的元素按原相对顺序进入下一轮。
                next_cur.push_back(cur[i]);
            }
        }
        cout << '\n';
        // 滚动数组：下一轮继续处理剩余序列。
        cur.swap(next_cur);
    }
    return 0;
}
