/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:48
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> line; // 当前队列，按从前到后的顺序保存学号
    for (int i = 1; i <= n; i++) {
        line.push_back(i);
    }

    for (int i = 1; i <= m; i++) {
        int student, move;
        cin >> student >> move;

        // 在队列中查找该学号当前所在的位置
        int position = 0;
        while (line[position] != student) {
            position++;
        }
        // 先出队，再按移动距离插回。
        // position 是删除前保存的下标：删除后插入到 position + move 正好对应向后/向前移动。
        line.erase(line.begin() + position);
        line.insert(line.begin() + position + move, student);
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