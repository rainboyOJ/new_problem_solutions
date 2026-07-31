/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 02:19
 */
#include <bits/stdc++.h>
using namespace std;

struct CacheLine {
    int block;
    int previous;
    int next;
    bool dirty;
};

struct CacheSet {
    int head;
    int tail;
    int used;
};

vector<CacheLine> lines;
vector<CacheSet> cache_sets;

void remove_from_lru(int group, int index) {
    int previous = lines[index].previous;
    int next = lines[index].next;

    if (previous == -1) cache_sets[group].head = next;
    else lines[previous].next = next;
    if (next == -1) cache_sets[group].tail = previous;
    else lines[next].previous = previous;

    lines[index].previous = -1;
    lines[index].next = -1;
}

void insert_to_front(int group, int index) {
    int old_head = cache_sets[group].head;
    lines[index].previous = -1;
    lines[index].next = old_head;
    if (old_head == -1) cache_sets[group].tail = index;
    else lines[old_head].previous = index;
    cache_sets[group].head = index;
}

void touch(int group, int index) {
    if (cache_sets[group].head == index) return;
    remove_from_lru(group, index);
    insert_to_front(group, index);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, group_count, q;
    cin >> n >> group_count >> q;

    lines.resize(n * group_count);
    cache_sets.resize(group_count);
    for (int group = 0; group < group_count; group++) {
        cache_sets[group].head = -1;
        cache_sets[group].tail = -1;
        cache_sets[group].used = 0;
    }
    unordered_map<int, int> location;
    location.reserve(q * 2 + 1);

    for (int operation = 1; operation <= q; operation++) {
        int type, block;
        cin >> type >> block;
        int group = (block / n) % group_count;

        unordered_map<int, int>::iterator found = location.find(block);
        if (found != location.end()) {
            int index = found->second;
            if (type == 1) lines[index].dirty = true;
            touch(group, index);
            continue;
        }

        // 未命中时先处理被替换缓存行的写回，再从内存读入新块。
        int index;
        if (cache_sets[group].used < n) {
            index = group * n + cache_sets[group].used;
            cache_sets[group].used++;
        } else {
            index = cache_sets[group].tail;
            if (lines[index].dirty) cout << "1 " << lines[index].block << '\n';
            location.erase(lines[index].block);
            remove_from_lru(group, index);
        }

        cout << "0 " << block << '\n';
        lines[index].block = block;
        lines[index].dirty = (type == 1);
        location[block] = index;
        insert_to_front(group, index);
    }

    return 0;
}
