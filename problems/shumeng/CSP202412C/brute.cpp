/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 02:19
 */
// brute.cpp：小数据暴力解，用 vector 直接扫描每组缓存中的所有缓存行。
#include <bits/stdc++.h>
using namespace std;

struct Entry {
    int block;
    bool dirty;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, group_count, q;
    cin >> n >> group_count >> q;
    vector<vector<Entry> > cache(group_count);

    for (int operation = 1; operation <= q; operation++) {
        int type, block;
        cin >> type >> block;
        int group = (block / n) % group_count;
        int hit = -1;
        for (int i = 0; i < (int)cache[group].size(); i++) {
            if (cache[group][i].block == block) {
                hit = i;
                break;
            }
        }

        if (hit != -1) {
            Entry entry = cache[group][hit];
            if (type == 1) entry.dirty = true;
            cache[group].erase(cache[group].begin() + hit);
            cache[group].insert(cache[group].begin(), entry);
            continue;
        }

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
