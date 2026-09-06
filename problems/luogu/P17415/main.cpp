/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-06 19:06
 * update_at: 2026-09-06 19:32
 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct TreapNode {
    int left;
    int right;
    int size;
    ll key;
    unsigned int priority;
};

vector<TreapNode> tree(1);
vector<int> recycled;
int root = 0;
unsigned int random_seed = 712367821u;
ll global_add = 0;
int low_mask = 0; // 当前所有小于 20 的可达钱数。

unsigned int next_random() {
    random_seed ^= random_seed << 13;
    random_seed ^= random_seed >> 17;
    random_seed ^= random_seed << 5;
    return random_seed;
}

int node_size(int node) {
    return node == 0 ? 0 : tree[node].size;
}

void pull(int node) {
    if (node != 0) {
        tree[node].size = node_size(tree[node].left)
            + node_size(tree[node].right) + 1;
    }
}

int new_node(ll key) {
    int id;
    if (recycled.empty()) {
        TreapNode node;
        node.left = node.right = 0;
        node.size = 1;
        node.key = key;
        node.priority = next_random();
        tree.push_back(node);
        id = (int)tree.size() - 1;
    } else {
        id = recycled.back();
        recycled.pop_back();
        tree[id].left = tree[id].right = 0;
        tree[id].size = 1;
        tree[id].key = key;
        tree[id].priority = next_random();
    }
    return id;
}

void release_tree(int node) {
    if (node == 0) {
        return;
    }
    vector<int> stack;
    stack.push_back(node);
    while (!stack.empty()) {
        int current = stack.back();
        stack.pop_back();
        if (tree[current].left != 0) {
            stack.push_back(tree[current].left);
        }
        if (tree[current].right != 0) {
            stack.push_back(tree[current].right);
        }
        recycled.push_back(current);
    }
}

// 按 key 切分：左树中的 key < key，右树中的 key >= key。
void split_tree(int current, ll key, int &left_tree, int &right_tree) {
    if (current == 0) {
        left_tree = right_tree = 0;
        return;
    }
    if (tree[current].key < key) {
        left_tree = current;
        split_tree(tree[current].right, key, tree[current].right, right_tree);
        pull(current);
    } else {
        right_tree = current;
        split_tree(tree[current].left, key, left_tree, tree[current].left);
        pull(current);
    }
}

bool contains_key(int current, ll key) {
    while (current != 0) {
        if (tree[current].key == key) {
            return true;
        }
        if (key < tree[current].key) {
            current = tree[current].left;
        } else {
            current = tree[current].right;
        }
    }
    return false;
}

int insert_node(int current, int node) {
    if (current == 0) {
        return node;
    }
    if (tree[node].priority > tree[current].priority) {
        split_tree(current, tree[node].key, tree[node].left, tree[node].right);
        pull(node);
        return node;
    }
    if (tree[node].key < tree[current].key) {
        tree[current].left = insert_node(tree[current].left, node);
    } else {
        tree[current].right = insert_node(tree[current].right, node);
    }
    pull(current);
    return current;
}

void insert_key(ll key) {
    if (contains_key(root, key)) {
        return;
    }
    root = insert_node(root, new_node(key));
}

void collect_values(int current, ll add, vector<ll> &values) {
    vector<int> stack;
    int p = current;
    while (p != 0 || !stack.empty()) {
        while (p != 0) {
            stack.push_back(p);
            p = tree[p].left;
        }
        p = stack.back();
        stack.pop_back();
        values.push_back(tree[p].key + add);
        p = tree[p].right;
    }
}

int build_from_sorted(const vector<ll> &values) {
    if (values.empty()) {
        return 0;
    }
    vector<int> stack;
    for (ll value : values) {
        int current = new_node(value);
        int last = 0;
        while (!stack.empty()
               && tree[stack.back()].priority < tree[current].priority) {
            last = stack.back();
            stack.pop_back();
        }
        tree[current].left = last;
        if (!stack.empty()) {
            tree[stack.back()].right = current;
        }
        stack.push_back(current);
    }
    int new_root = stack.front();
    vector<int> order;
    order.push_back(new_root);
    for (size_t i = 0; i < order.size(); i++) {
        int current = order[i];
        if (tree[current].left != 0) {
            order.push_back(tree[current].left);
        }
        if (tree[current].right != 0) {
            order.push_back(tree[current].right);
        }
    }
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        pull(order[i]);
    }
    return new_root;
}

void apply_ordinary(int a, int b) {
    int old_low = low_mask;
    low_mask = 0;
    vector<int> high_outputs;
    for (int value = 1; value < 20; value++) {
        if ((old_low & (1 << value)) == 0) {
            continue;
        }
        int output = value;
        if (value >= a) {
            output = value - a + b;
        }
        if (output < 20) {
            low_mask |= 1 << output;
        } else {
            high_outputs.push_back(output);
        }
    }

    global_add += (ll)b - a;
    int fallen = 0;
    split_tree(root, 20 - global_add, fallen, root);
    vector<ll> fallen_values;
    collect_values(fallen, global_add, fallen_values);
    for (ll value : fallen_values) {
        if (value >= 0 && value < 20) {
            low_mask |= 1 << (int)value;
        }
    }
    release_tree(fallen);

    for (int output : high_outputs) {
        insert_key((ll)output - global_add);
    }
}

void apply_special(int a, int b, int c) {
    ll delta_b = (ll)b - a;
    ll delta_c = (ll)c - a;
    vector<ll> high_values;
    collect_values(root, global_add, high_values);

    // 三个有序序列分别对应“不使用、使用并得到 b、使用并得到 c”。
    vector<ll> merged_high;
    size_t p0 = 0, p1 = 0, p2 = 0;
    while (p0 < high_values.size() || p1 < high_values.size()
           || p2 < high_values.size()) {
        ll next_value = LLONG_MAX;
        if (p0 < high_values.size()) {
            next_value = min(next_value, high_values[p0]);
        }
        if (p1 < high_values.size()) {
            next_value = min(next_value, high_values[p1] + delta_b);
        }
        if (p2 < high_values.size()) {
            next_value = min(next_value, high_values[p2] + delta_c);
        }
        merged_high.push_back(next_value);
        while (p0 < high_values.size() && high_values[p0] == next_value) {
            p0++;
        }
        while (p1 < high_values.size()
               && high_values[p1] + delta_b == next_value) {
            p1++;
        }
        while (p2 < high_values.size()
               && high_values[p2] + delta_c == next_value) {
            p2++;
        }
    }

    vector<ll> small_outputs;
    for (int value = 1; value < 20; value++) {
        if ((low_mask & (1 << value)) == 0) {
            continue;
        }
        small_outputs.push_back(value); // 不使用特殊机器。
        if (value >= a) {
            small_outputs.push_back(value + delta_b);
            small_outputs.push_back(value + delta_c);
        }
    }
    sort(small_outputs.begin(), small_outputs.end());
    small_outputs.erase(unique(small_outputs.begin(), small_outputs.end()),
                        small_outputs.end());

    vector<ll> all_values;
    size_t i = 0, j = 0;
    while (i < merged_high.size() || j < small_outputs.size()) {
        ll value;
        if (j == small_outputs.size()
            || (i < merged_high.size() && merged_high[i] < small_outputs[j])) {
            value = merged_high[i++];
        } else if (i == merged_high.size()
                   || small_outputs[j] < merged_high[i]) {
            value = small_outputs[j++];
        } else {
            value = merged_high[i];
            i++;
            j++;
        }
        if (all_values.empty() || all_values.back() != value) {
            all_values.push_back(value);
        }
    }

    release_tree(root);
    root = 0;
    global_add = 0;
    low_mask = 0;
    vector<ll> high_after;
    for (ll value : all_values) {
        if (value < 20) {
            low_mask |= 1 << (int)value;
        } else {
            high_after.push_back(value);
        }
    }
    root = build_from_sorted(high_after);
}

bool reachable(ll value) {
    if (value >= 0 && value < 20) {
        return (low_mask & (1 << (int)value)) != 0;
    }
    return contains_key(root, value - global_add);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x, q;
    cin >> n >> x >> q;
    tree.reserve(600000);

    // 初始状态单独放入集合；题目保证 x>=1。
    if (x < 20) {
        low_mask |= 1 << x;
    } else {
        insert_key(x);
    }

    for (int i = 0; i < n; i++) {
        int type;
        cin >> type;
        if (type == 0) {
            int a, b;
            cin >> a >> b;
            apply_ordinary(a, b);
        } else {
            int a, b, c;
            cin >> a >> b >> c;
            apply_special(a, b, c);
        }
    }

    while (q--) {
        ll y;
        cin >> y;
        cout << (reachable(y) ? 1 : 0) << '\n';
    }
    return 0;
}
