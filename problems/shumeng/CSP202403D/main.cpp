/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
#include <bits/stdc++.h>
using namespace std;

map<int, int> water;  // water[pos] 表示位置 pos 当前的水滴数，只保存有水的格子
priority_queue<int, vector<int>, greater<int> > exploding; // 待爆炸位置，小根堆保证最左的先爆

// 给位置 pos 加一滴水，达到 5 滴就加入待爆堆
void add_water(int pos) {
    water[pos]++;
    if (water[pos] >= 5) exploding.push(pos);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int c, m, operation_count;
    cin >> c >> m >> operation_count;
    for (int i = 0; i < m; i++) {
        int pos, cnt;
        cin >> pos >> cnt;
        water[pos] = cnt;
    }

    while (operation_count--) {
        int position;
        cin >> position;
        add_water(position);

        // 处理连锁爆炸，直到没有待爆格子
        while (!exploding.empty()) {
            int current = exploding.top();
            exploding.pop();
            map<int, int>::iterator it = water.find(current);
            if (it == water.end() || it->second < 5) continue; // 已被之前的爆炸清空

            // 先记住左右相邻的有水格子，再删除当前格子
            map<int, int>::iterator left = it;
            bool has_left = (left != water.begin());
            if (has_left) --left;
            map<int, int>::iterator right = it;
            ++right;
            bool has_right = (right != water.end());
            water.erase(it);

            if (has_left) add_water(left->first);
            if (has_right) add_water(right->first);
        }

        cout << water.size() << '\n';
    }

    return 0;
}