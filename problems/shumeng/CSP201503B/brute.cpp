/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 18:50
 */
// brute.cpp：小数据基准，枚举不同数字并反复选择当前应输出的数字。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> numbers(n);
    for (int i = 0; i < n; i++) cin >> numbers[i];

    vector<int> values;
    for (int i = 0; i < n; i++) {
        bool exists = false;
        for (int j = 0; j < (int)values.size(); j++) {
            if (values[j] == numbers[i]) exists = true;
        }
        if (!exists) values.push_back(numbers[i]);
    }

    vector<int> count(values.size(), 0);
    for (int i = 0; i < (int)values.size(); i++) {
        for (int j = 0; j < n; j++) {
            if (numbers[j] == values[i]) count[i]++;
        }
    }

    vector<int> used(values.size(), 0);
    for (int round = 0; round < (int)values.size(); round++) {
        int best = -1;
        for (int i = 0; i < (int)values.size(); i++) {
            if (used[i]) continue;
            if (best == -1 || count[i] > count[best] ||
                (count[i] == count[best] && values[i] < values[best])) {
                best = i;
            }
        }
        used[best] = 1;
        cout << values[best] << ' ' << count[best] << '\n';
    }

    return 0;
}
