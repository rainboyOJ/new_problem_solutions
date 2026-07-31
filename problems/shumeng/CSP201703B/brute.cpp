/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:42
 */
// brute.cpp：逐次交换相邻学生，直接模拟向前或向后移动。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> line(n);
    for (int i = 0; i < n; i++) {
        line[i] = i + 1;
    }

    for (int i = 1; i <= m; i++) {
        int student, move;
        cin >> student >> move;
        int position = 0;
        while (line[position] != student) {
            position++;
        }

        if (move > 0) {
            for (int step = 0; step < move; step++) {
                swap(line[position], line[position + 1]);
                position++;
            }
        } else {
            for (int step = 0; step < -move; step++) {
                swap(line[position], line[position - 1]);
                position--;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << line[i];
    }
    cout << '\n';

    return 0;
}
