/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-28 18:13
 * update_at: 2026-07-28 18:15
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;

int n, target;
int nums[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> target;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    unordered_map<int, int> idx;
    for (int i = 0; i < n; i++) {
        int complement = target - nums[i];
        if (auto it = idx.find(complement); it != idx.end()) {
            cout << it->second << ' ' << i << '\n';
            return 0;
        }
        idx[nums[i]] = i;
    }

    return 0;
}
