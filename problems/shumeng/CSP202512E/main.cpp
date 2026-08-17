/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-08-17 23:10
 */
#include <bits/stdc++.h>
using namespace std;

const int MAX_VALUE_BIT = 29;          // 值域 [0,10^9] 的二进制最高位
const int MAX_TOTAL_ELEMENT = 500000;  // 所有数据包元素总数上限
const int MAX_TRIE_NODE = MAX_TOTAL_ELEMENT * (MAX_VALUE_BIT + 1) + 5;

struct TrieNode {
    int child[2]; // 0/1 两个子节点下标
    int count;    // 子树内元素个数
    int best;     // 该子树对应冲突图的最大团大小（即该子树的维修代价）
    int version;  // 版本号，用于判断跨子树缓存是否过期
};

struct CrossCache {
    int version_left;  // 左子树版本
    int version_right; // 右子树版本
    int value;         // 缓存的跨子树结果
};

int n;
long long threshold_w;   // 稳定阈值 W
int highest_bit;         // W 的最高位所在位置
int low_threshold;       // W 去掉最高位后的低位部分
bool all_pairs_conflict; // W >= 2^30 时任意两元素异或都小于 W，全部互斥
TrieNode trie[MAX_TRIE_NODE];
int trie_nodes;
unordered_map<unsigned long long, CrossCache> cross_cache; // 跨子树状态缓存

// 两个节点下标拼成一个 key，用于跨子树缓存
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

// 从两个低位 Trie 中选取元素，使任意跨侧异或小于 limit 时能选出的最大总数。
// 这是冲突图最大团的递归计算核心
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

    // 用版本号判断缓存是否仍有效
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
        // 低位限制的当前位为 0：只能选同一位分支，取最大值
        int same_zero = cross_value(trie[left].child[0],
                                    trie[right].child[0], bit - 1, limit);
        int same_one = cross_value(trie[left].child[1],
                                   trie[right].child[1], bit - 1, limit);
        result = max(max(get_count(left), get_count(right)),
                     max(same_zero, same_one));
    } else {
        // 当前位为 1：两个反向分支互不影响，可以同时选
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

// 重新计算节点 u 的 best：看左右子树的单侧最大团与跨侧最大团
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

// 向 Trie 插入一个值，沿路径更新计数并刷新各节点的 best
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

// 合并两棵 Trie（按大小启发式），返回合并后的根
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
