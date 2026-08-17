/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
// brute.cpp：小数据暴力解，显式修改父子关系并沿父指针计算深度，只适合小规模对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005;

int n, operation_count;
int parent[MAXN];          // 当前的父文件夹
vector<int> child[MAXN];   // 当前每个文件夹的直接子文件夹
long long folder_data[MAXN]; // 当前文件夹直接拥有的数据量
bool alive[MAXN];          // 文件夹是否仍然存在（未被合并删除）

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> operation_count;
    for (int i = 2; i <= n; i++) {
        cin >> parent[i];
        child[parent[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++) cin >> folder_data[i];
    for (int i = 1; i <= n; i++) alive[i] = true;

    while (operation_count--) {
        int type, node;
        cin >> type >> node;
        if (type == 1) {
            // 合并：删除 node 的所有直接子文件夹，把它们的子文件夹提升上来
            vector<int> old_child = child[node];
            child[node].clear();
            for (int i = 0; i < (int)old_child.size(); i++) {
                int removed = old_child[i];
                folder_data[node] += folder_data[removed];
                alive[removed] = false;
                // 被删子文件夹的子文件夹改为 node 的直接子文件夹
                for (int j = 0; j < (int)child[removed].size(); j++) {
                    int promoted = child[removed][j];
                    parent[promoted] = node;
                    child[node].push_back(promoted);
                }
                child[removed].clear();
            }
            cout << child[node].size() << ' ' << folder_data[node] << '\n';
        } else {
            // 访问：沿父指针向上走，统计路径上存活的文件夹数量
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