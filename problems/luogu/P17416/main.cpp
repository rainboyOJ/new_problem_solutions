/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-06 19:06
 * update_at: 2026-09-06 19:22
 */
#include <bits/stdc++.h>
using namespace std;
const int MAX_BIT = 30;

struct TrieNode {
    int child[2];
    int left_rank;
    int right_rank;
    int count;
};

int n, k;
vector<int> value_list;
vector<TrieNode> trie;
vector<vector<int> > prefix_one;

int new_node() {
    TrieNode node;
    node.child[0] = node.child[1] = 0;
    node.left_rank = n;
    node.right_rank = 0;
    node.count = 0;
    trie.push_back(node);
    return (int)trie.size() - 1;
}

// 建立完整的值域 Trie，同时记录每个节点对应的排序下标区间。
void build_structure(int value, int rank) {
    int p = 1;
    trie[p].left_rank = min(trie[p].left_rank, rank);
    trie[p].right_rank = max(trie[p].right_rank, rank + 1);
    for (int bit = MAX_BIT; bit >= 0; bit--) {
        int direction = (value >> bit) & 1;
        if (trie[p].child[direction] == 0) {
            trie[p].child[direction] = new_node();
        }
        p = trie[p].child[direction];
        trie[p].left_rank = min(trie[p].left_rank, rank);
        trie[p].right_rank = max(trie[p].right_rank, rank + 1);
    }
}

// 激活排序下标为 rank 的数。当前时刻激活的元素总是一个前缀。
void activate(int value) {
    int p = 1;
    trie[p].count++;
    for (int bit = MAX_BIT; bit >= 0; bit--) {
        int direction = (value >> bit) & 1;
        p = trie[p].child[direction];
        trie[p].count++;
    }
}

// 计算一个 Trie 节点中当前已激活元素的 xor 总和。
long long sum_xor(int node, int x, int activated_prefix, int highest_bit) {
    int left = trie[node].left_rank;
    int right = min(trie[node].right_rank, activated_prefix);
    if (left >= right) {
        return 0;
    }

    long long result = 0;
    for (int bit = 0; bit <= highest_bit; bit++) {
        int ones = prefix_one[bit][right] - prefix_one[bit][left];
        int total = right - left;
        int xor_ones = ((x >> bit) & 1) ? total - ones : ones;
        result += (long long)xor_ones * (1LL << bit);
    }
    return result;
}

// 查询当前集合中最大的 need 个 (value xor x) 之和。
long long query_top_sum(int node, int bit, int x, int need, int activated_prefix) {
    if (need == 0 || bit < 0) {
        return 0;
    }

    int x_bit = (x >> bit) & 1;
    int preferred = x_bit ^ 1; // 这一支在当前位产生 1，更优先。
    int other = x_bit;
    int preferred_node = trie[node].child[preferred];
    int preferred_count = preferred_node == 0 ? 0 : trie[preferred_node].count;

    if (preferred_count >= need) {
        return (long long)need * (1LL << bit)
            + query_top_sum(preferred_node, bit - 1, x, need,
                            activated_prefix);
    }

    long long result = 0;
    if (preferred_count > 0) {
        result += sum_xor(preferred_node, x, activated_prefix, bit);
    }
    int other_node = trie[node].child[other];
    result += query_top_sum(other_node, bit - 1, x, need - preferred_count,
                            activated_prefix);
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    value_list.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> value_list[i];
    }
    sort(value_list.begin(), value_list.end());

    prefix_one.assign(MAX_BIT + 1, vector<int>(n + 1, 0));
    for (int bit = 0; bit <= MAX_BIT; bit++) {
        for (int i = 0; i < n; i++) {
            prefix_one[bit][i + 1] = prefix_one[bit][i]
                + ((value_list[i] >> bit) & 1);
        }
    }

    trie.reserve(n * (MAX_BIT + 1) + 5);
    trie.push_back(TrieNode());
    new_node(); // 根节点编号固定为 1。
    for (int i = 0; i < n; i++) {
        build_structure(value_list[i], i);
    }

    long long answer = 0;
    for (int i = 0; i < n; i++) {
        // 把当前值作为被选子序列中的最后一个最大值，
        // 其余 k-1 个元素只能来自排序前缀。
        if (i >= k - 1) {
            long long candidate = query_top_sum(1, MAX_BIT, value_list[i],
                                                k - 1, i);
            answer = max(answer, candidate);
        }
        activate(value_list[i]);
    }

    cout << answer << '\n';
    return 0;
}
