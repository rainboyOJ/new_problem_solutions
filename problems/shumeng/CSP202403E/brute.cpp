/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 22:55
 */
// brute.cpp：小数据暴力解，显式修改父子关系并沿父指针计算深度。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, operation_count;
    cin >> n >> operation_count;
    vector<int> parent(n + 1, 0);
    vector<vector<int> > child(n + 1);
    for (int i = 2; i <= n; i++) {
        cin >> parent[i];
        child[parent[i]].push_back(i);
    }
    vector<long long> folder_data(n + 1);
    for (int i = 1; i <= n; i++) cin >> folder_data[i];
    vector<char> alive(n + 1, 1);

    while (operation_count--) {
        int type, node;
        cin >> type >> node;
        if (type == 1) {
            vector<int> old_child = child[node];
            child[node].clear();
            for (int i = 0; i < (int)old_child.size(); i++) {
                int removed = old_child[i];
                folder_data[node] += folder_data[removed];
                alive[removed] = 0;
                for (int j = 0; j < (int)child[removed].size(); j++) {
                    int promoted = child[removed][j];
                    parent[promoted] = node;
                    child[node].push_back(promoted);
                }
                child[removed].clear();
            }
            cout << child[node].size() << ' ' << folder_data[node] << '\n';
        } else {
            int count = 1;
            int current = node;
            while (parent[current] != 0) {
                current = parent[current];
                if (alive[current]) count++;
            }
            cout << count << '\n';
        }
    }

    return 0;
}
