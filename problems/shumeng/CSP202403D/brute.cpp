/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 23:05
 */
// brute.cpp：小数据暴力解，使用有序数组线性寻找左右相邻格子。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int c, m, operation_count;
    cin >> c >> m >> operation_count;
    vector<pair<int, int> > water;
    for (int i = 0; i < m; i++) {
        pair<int, int> current;
        cin >> current.first >> current.second;
        water.push_back(current);
    }
    sort(water.begin(), water.end());

    while (operation_count--) {
        int position;
        cin >> position;
        vector<int> exploding;
        for (int i = 0; i < (int)water.size(); i++) {
            if (water[i].first == position) {
                water[i].second++;
                if (water[i].second >= 5) exploding.push_back(position);
                break;
            }
        }
        while (!exploding.empty()) {
            sort(exploding.begin(), exploding.end());
            int current = exploding[0];
            exploding.erase(exploding.begin());
            vector<pair<int, int> >::iterator current_it = lower_bound(
                water.begin(), water.end(), make_pair(current, -1));
            if (current_it == water.end() || current_it->first != current
                    || current_it->second < 5) continue;
            int index = current_it - water.begin();
            water.erase(water.begin() + index);
            if (index - 1 >= 0) {
                water[index - 1].second++;
                if (water[index - 1].second >= 5) exploding.push_back(water[index - 1].first);
            }
            if (index < (int)water.size()) {
                water[index].second++;
                if (water[index].second >= 5) exploding.push_back(water[index].first);
            }
        }
        cout << water.size() << '\n';
    }

    return 0;
}
