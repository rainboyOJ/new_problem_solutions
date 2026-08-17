/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
#include <bits/stdc++.h>
using namespace std;

struct SequenceNode {
    int left, right;
    int priority;
    int key, color;
    int size;
    int first_color, last_color;
    int run_count;
};

vector<SequenceNode> sequence_tree;

int sequence_size(int root) {
    return root == 0 ? 0 : sequence_tree[root].size;
}

void pull_sequence(int root) {
    if (root == 0) return;
    SequenceNode &node = sequence_tree[root];
    node.size = sequence_size(node.left) + sequence_size(node.right) + 1;
    node.first_color = node.left == 0 ? node.color : sequence_tree[node.left].first_color;
    node.last_color = node.right == 0 ? node.color : sequence_tree[node.right].last_color;
    node.run_count = sequence_tree[node.left].run_count + 1 + sequence_tree[node.right].run_count;
    if (node.left != 0 && sequence_tree[node.left].last_color == node.color) node.run_count--;
    if (node.right != 0 && node.color == sequence_tree[node.right].first_color) node.run_count--;
}

int merge_sequence(int left_root, int right_root) {
    if (left_root == 0) return right_root;
    if (right_root == 0) return left_root;
    if (sequence_tree[left_root].priority > sequence_tree[right_root].priority) {
        sequence_tree[left_root].right = merge_sequence(sequence_tree[left_root].right, right_root);
        pull_sequence(left_root);
        return left_root;
    }
    sequence_tree[right_root].left = merge_sequence(left_root, sequence_tree[right_root].left);
    pull_sequence(right_root);
    return right_root;
}

void split_sequence(int root, int key, int &left_root, int &right_root) {
    if (root == 0) {
        left_root = 0;
        right_root = 0;
        return;
    }
    if (sequence_tree[root].key <= key) {
        left_root = root;
        split_sequence(sequence_tree[root].right, key, sequence_tree[root].right, right_root);
        pull_sequence(left_root);
    } else {
        right_root = root;
        split_sequence(sequence_tree[root].left, key, left_root, sequence_tree[root].left);
        pull_sequence(right_root);
    }
}

void collect_colors(int root, unordered_map<int, int> &count) {
    if (root == 0) return;
    collect_colors(sequence_tree[root].left, count);
    count[sequence_tree[root].color]++;
    collect_colors(sequence_tree[root].right, count);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<int> color(n + 1);
    for (int i = 1; i <= n; i++) cin >> color[i];

    sequence_tree.assign(n + 1, SequenceNode());
    mt19937 random_engine(712367821);
    int initial_root = 0;
    for (int i = 1; i <= n; i++) {
        sequence_tree[i].left = 0;
        sequence_tree[i].right = 0;
        sequence_tree[i].priority = (int)random_engine();
        sequence_tree[i].key = i;
        sequence_tree[i].color = color[i];
        sequence_tree[i].size = 1;
        sequence_tree[i].first_color = color[i];
        sequence_tree[i].last_color = color[i];
        sequence_tree[i].run_count = 1;
        initial_root = merge_sequence(initial_root, i);
    }

    vector<int> board_root(k + 2, 0);
    vector<unique_ptr<unordered_map<int, int> > > board_colors(k + 2);
    board_root[1] = initial_root;
    board_colors[1].reset(new unordered_map<int, int>());
    board_colors[1]->reserve(n * 2 + 1);
    for (int i = 1; i <= n; i++) (*board_colors[1])[color[i]]++;

    for (int operation = 1; operation <= k; operation++) {
        int source_board, left_key, right_key;
        cin >> source_board >> left_key >> right_key;

        int left_root, middle_root, right_root;
        int temporary_root;
        split_sequence(board_root[source_board], left_key - 1, left_root, temporary_root);
        split_sequence(temporary_root, right_key, middle_root, right_root);
        int remaining_root = merge_sequence(left_root, right_root);
        int middle_size = sequence_size(middle_root);
        int remaining_size = sequence_size(remaining_root);

        int small_size = min(middle_size, remaining_size);
        unique_ptr<unordered_map<int, int> > small_colors(new unordered_map<int, int>());
        small_colors->reserve(small_size * 2 + 1);
        if (middle_size <= remaining_size) collect_colors(middle_root, *small_colors);
        else collect_colors(remaining_root, *small_colors);

        unique_ptr<unordered_map<int, int> > old_colors = move(board_colors[source_board]);
        unordered_map<int, int>::iterator iterator = small_colors->begin();
        while (iterator != small_colors->end()) {
            unordered_map<int, int>::iterator old_iterator = old_colors->find(iterator->first);
            old_iterator->second -= iterator->second;
            if (old_iterator->second == 0) old_colors->erase(old_iterator);
            ++iterator;
        }

        if (middle_size <= remaining_size) {
            board_root[source_board] = remaining_root;
            board_root[operation + 1] = middle_root;
            board_colors[source_board] = move(old_colors);
            board_colors[operation + 1] = move(small_colors);
        } else {
            board_root[source_board] = remaining_root;
            board_root[operation + 1] = middle_root;
            board_colors[source_board] = move(small_colors);
            board_colors[operation + 1] = move(old_colors);
        }

        if (middle_root == 0) cout << "0 0\n";
        else cout << board_colors[operation + 1]->size() << ' '
                  << sequence_tree[middle_root].run_count << '\n';
    }
    return 0;
}
