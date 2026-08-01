/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-08-01 12:10
 */
#include <bits/stdc++.h>
using namespace std;

const int MAX_VALUE_BIT = 29;
const int MAX_TOTAL_ELEMENT = 500000;
const int MAX_TRIE_NODE = MAX_TOTAL_ELEMENT * (MAX_VALUE_BIT + 1) + 5;

struct TrieNode {
    int child[2];
    int count;
    int best;
    int version;
};

struct CrossCache {
    int version_left;
    int version_right;
    int value;
};

int n;
long long threshold_w;
int highest_bit;
int low_threshold;
bool all_pairs_conflict;
TrieNode trie[MAX_TRIE_NODE];
int trie_nodes;
unordered_map<unsigned long long, CrossCache> cross_cache;

unsigned long long pair_key(int x, int y) {
    if (x > y) {
        swap(x, y);
    }
    return (unsigned long long)(unsigned int)x << 32
           | (unsigned int)y;
}

int get_count(int u) {
    return u == 0 ? 0 : trie[u].count;
}

int new_node() {
    trie_nodes++;
    trie[trie_nodes].child[0] = 0;
    trie[trie_nodes].child[1] = 0;
    trie[trie_nodes].count = 0;
    trie[trie_nodes].best = 0;
    trie[trie_nodes].version = 0;
    return trie_nodes;
}

int cross_value(int left, int right, int bit, int limit) {
    if (left == 0 && right == 0) {
        return 0;
    }
    if (left == 0) {
        return get_count(right);
    }
    if (right == 0) {
        return get_count(left);
    }
    if (limit == 0) {
        return max(get_count(left), get_count(right));
    }
    if (bit < 0) {
        return get_count(left) + get_count(right);
    }

    unsigned long long key = pair_key(left, right);
    unordered_map<unsigned long long, CrossCache>::iterator it;
    it = cross_cache.find(key);
    if (it != cross_cache.end()
        && it->second.version_left == trie[left].version
        && it->second.version_right == trie[right].version) {
        return it->second.value;
    }

    int result;
    if (((limit >> bit) & 1) == 0) {
        int same_zero = cross_value(trie[left].child[0],
                                    trie[right].child[0], bit - 1, limit);
        int same_one = cross_value(trie[left].child[1],
                                   trie[right].child[1], bit - 1, limit);
        result = max(max(get_count(left), get_count(right)),
                     max(same_zero, same_one));
    } else {
        int lower_limit = limit ^ (1 << bit);
        int different_zero = cross_value(trie[left].child[0],
                                         trie[right].child[1],
                                         bit - 1, lower_limit);
        int different_one = cross_value(trie[left].child[1],
                                        trie[right].child[0],
                                        bit - 1, lower_limit);
        result = different_zero + different_one;
    }

    CrossCache cache;
    cache.version_left = trie[left].version;
    cache.version_right = trie[right].version;
    cache.value = result;
    cross_cache[key] = cache;
    return result;
}

void update_best(int u, int bit) {
    if (bit > highest_bit) {
        trie[u].best = max(trie[trie[u].child[0]].best,
                           trie[trie[u].child[1]].best);
    } else if (bit == highest_bit) {
        int left_count = get_count(trie[u].child[0]);
        int right_count = get_count(trie[u].child[1]);
        int cross = cross_value(trie[u].child[0], trie[u].child[1],
                                highest_bit - 1, low_threshold);
        trie[u].best = max(max(left_count, right_count), cross);
    }
}

void insert_value(int &u, int bit, int value) {
    if (u == 0) {
        u = new_node();
    }
    trie[u].count++;
    trie[u].version++;
    if (bit < 0) {
        return;
    }
    int direction = (value >> bit) & 1;
    insert_value(trie[u].child[direction], bit - 1, value);
    update_best(u, bit);
}

int merge_trie(int left, int right, int bit) {
    if (left == 0) {
        return right;
    }
    if (right == 0) {
        return left;
    }
    if (trie[left].count < trie[right].count) {
        swap(left, right);
    }
    trie[left].count += trie[right].count;
    trie[left].version++;
    if (bit >= 0) {
        trie[left].child[0] = merge_trie(trie[left].child[0],
                                          trie[right].child[0], bit - 1);
        trie[left].child[1] = merge_trie(trie[left].child[1],
                                          trie[right].child[1], bit - 1);
        update_best(left, bit);
    }
    return left;
}

int packet_cost(int root) {
    if (root == 0) {
        return 0;
    }
    if (all_pairs_conflict) {
        return trie[root].count;
    }
    return trie[root].best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> threshold_w;
    highest_bit = 0;
    long long temp_w = threshold_w;
    while (temp_w > 1) {
        temp_w >>= 1;
        highest_bit++;
    }
    all_pairs_conflict = threshold_w >= (1LL << 30);
    if (all_pairs_conflict) {
        highest_bit = MAX_VALUE_BIT;
        low_threshold = 0;
    } else {
        low_threshold = (int)(threshold_w - (1LL << highest_bit));
    }
    cross_cache.reserve(1 << 20);

    vector<int> packet_root(n + 1, 0);
    vector<int> packet_size(n + 1, 0);
    long long total_cost = 0;
    for (int i = 1; i <= n; i++) {
        int count;
        cin >> count;
        packet_size[i] = count;
        for (int j = 0; j < count; j++) {
            int value;
            cin >> value;
            insert_value(packet_root[i], MAX_VALUE_BIT, value);
        }
        total_cost += packet_cost(packet_root[i]);
    }

    int q;
    cin >> q;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int u, value;
            cin >> u >> value;
            total_cost -= packet_cost(packet_root[u]);
            insert_value(packet_root[u], MAX_VALUE_BIT, value);
            packet_size[u]++;
            total_cost += packet_cost(packet_root[u]);
        } else if (type == 2) {
            int u, v;
            cin >> u >> v;
            total_cost -= packet_cost(packet_root[u]);
            total_cost -= packet_cost(packet_root[v]);
            packet_root[u] = merge_trie(packet_root[u], packet_root[v],
                                        MAX_VALUE_BIT);
            packet_size[u] += packet_size[v];
            packet_root[v] = 0;
            packet_size[v] = 0;
            total_cost += packet_cost(packet_root[u]);
        } else {
            cout << total_cost << '\n';
        }
    }
    return 0;
}
