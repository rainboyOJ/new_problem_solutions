/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 18:50
 */
#include <bits/stdc++.h>
using namespace std;

int count_value[1005];

struct Item {
    int value;
    int count;
};

bool compare_item(const Item &left, const Item &right) {
    if (left.count != right.count) return left.count > right.count;
    return left.value < right.value;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int value;
        cin >> value;
        count_value[value]++;
    }

    vector<Item> items;
    for (int value = 0; value <= 1000; value++) {
        if (count_value[value] > 0) {
            Item current = {value, count_value[value]};
            items.push_back(current);
        }
    }
    sort(items.begin(), items.end(), compare_item);

    for (int i = 0; i < (int)items.size(); i++) {
        cout << items[i].value << ' ' << items[i].count << '\n';
    }

    return 0;
}
