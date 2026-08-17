/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
// brute.cpp：小数据暴力解，用 vector 顺序扫描每组中的缓存行来模拟 LRU。
#include <bits/stdc++.h>
using namespace std;

struct Entry {
    int block;  // 缓存行保存的内存块编号
    bool dirty; // 是否被写改过
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, group_count, q;
    cin >> n >> group_count >> q;
    vector<vector<Entry> > cache(group_count); // 每组一个 vector，表头是最新使用的

    for (int operation = 1; operation <= q; operation++) {
        int type, block;
        cin >> type >> block;
        int group = (block / n) % group_count;

        // 线性查找当前组是否已缓存该块
        int hit = -1;
        for (int i = 0; i < (int)cache[group].size(); i++) {
            if (cache[group][i].block == block) {
                hit = i;
                break;
            }
        }

        if (hit != -1) {
            // 命中：按操作更新脏位，并移到表头
            Entry entry = cache[group][hit];
            if (type == 1) entry.dirty = true;
            cache[group].erase(cache[group].begin() + hit);
            cache[group].insert(cache[group].begin(), entry);
            continue;
        }

        // 未命中且已满：先写回最久未使用的脏块，再淘汰
        if ((int)cache[group].size() == n) {
            Entry victim = cache[group].back();
            if (victim.dirty) cout << "1 " << victim.block << '\n';
            cache[group].pop_back();
        }
        cout << "0 " << block << '\n';
        Entry entry;
        entry.block = block;
        entry.dirty = (type == 1);
        cache[group].insert(cache[group].begin(), entry);
    }

    return 0;
}
