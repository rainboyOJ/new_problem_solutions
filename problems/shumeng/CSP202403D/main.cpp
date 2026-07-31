/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 23:05
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int c, m, operation_count;
    cin >> c >> m >> operation_count;
    map<int, int> water;
    for (int i = 0; i < m; i++) {
        int position, count;
        cin >> position >> count;
        water[position] = count;
    }

    while (operation_count--) {
        int position;
        cin >> position;
        water[position]++;
        priority_queue<int, vector<int>, greater<int> > exploding;
        if (water[position] >= 5) exploding.push(position);

        while (!exploding.empty()) {
            int current = exploding.top();
            exploding.pop();
            map<int, int>::iterator it = water.find(current);
            if (it == water.end() || it->second < 5) continue;

            map<int, int>::iterator left = it;
            map<int, int>::iterator right = it;
            bool has_left = it != water.begin();
            if (has_left) --left;
            ++right;
            bool has_right = right != water.end();
            water.erase(it);

            if (has_left) {
                left->second++;
                if (left->second == 5) exploding.push(left->first);
            }
            if (has_right) {
                right->second++;
                if (right->second == 5) exploding.push(right->first);
            }
        }
        cout << water.size() << '\n';
    }

    return 0;
}
