/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-11 10:18
 * update_at: 2026-08-12 14:07
 */
// main-link.cpp：另一种解法，用链表维护当前剩余序列的连续原数组段。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

int n;
int a[MAXN];

// 每个节点表示当前序列中的一个连续段：a[start_pos] ... a[start_pos + len - 1]
int start_pos[MAXN * 3]; // 段在原数组中的起始下标
int seg_len[MAXN * 3];   // 段长度
int nxt[MAXN * 3];       // 段链表：后继节点
int pre[MAXN * 3];       // 段链表：前驱节点
int node_cnt;            // 已分配的节点数
int head_node;           // 段链表头节点

// 本轮要删除的位置记录：第 i 个删除点落在 deleted_node[i] 段内，偏移为 deleted_offset[i]。
int deleted_node[MAXN];
int deleted_offset[MAXN]; // 段内 1-based 偏移，表示该位置在段内的第几个元素
int deleted_value[MAXN];
int delete_cnt;

vector<vector<int> > rounds;

// 新建一个连续段节点：原数组从 pos 开始、长度为 len；len <= 0 返回空节点。
int new_node(int pos, int len) {
    if (len <= 0) return 0;
    node_cnt++;
    start_pos[node_cnt] = pos;
    seg_len[node_cnt] = len;
    nxt[node_cnt] = 0;
    pre[node_cnt] = 0;
    return node_cnt;
}

// 在节点 x 之后插入节点 y。
void insert_after(int x, int y) {
    if (y == 0) return;
    int z = nxt[x];
    nxt[x] = y;
    pre[y] = x;
    nxt[y] = z;
    if (z != 0) pre[z] = y;
}

// 从链表中摘掉节点 x。
void erase_node(int x) {
    int l = pre[x];
    int r = nxt[x];
    if (l != 0) nxt[l] = r;
    if (r != 0) pre[r] = l;
    if (head_node == x) head_node = r;
}

// 把段 x 在段内 1-based 偏移 offset 处切开，替换为左右两个新段。
void replace_by_split(int x, int offset) {
    int left_len = offset - 1;
    int right_len = seg_len[x] - offset;
    int old_start = start_pos[x];
    int left_node = new_node(old_start, left_len);
    int right_node = new_node(old_start + offset, right_len);

    int l = pre[x];
    int r = nxt[x];
    if (l != 0) nxt[l] = 0;
    if (r != 0) pre[r] = 0;

    if (l != 0) {
        nxt[l] = r;
        if (r != 0) pre[r] = l;
    }
    erase_node(x);

    // 按顺序把新段插回原位置。
    int first = 0;
    int last = l;
    if (left_node != 0) {
        if (l != 0) insert_after(l, left_node);
        else head_node = left_node;
        first = left_node;
        last = left_node;
    }
    if (right_node != 0) {
        if (last != 0) insert_after(last, right_node);
        else head_node = right_node;
        if (first == 0) first = right_node;
        last = right_node;
    }
    if (last != 0) {
        nxt[last] = r;
        if (r != 0) pre[r] = last;
    }
    else {
        if (l != 0) nxt[l] = r;
        if (r != 0) pre[r] = l;
        if (l == 0) head_node = r;
    }
}

// 定位本轮要删除的排名：1^3, 2^3, ... 递增，用 cur 指针从链表头往后扫。
// 只记录删除点（节点 + 段内偏移），本轮内不修改链表。
void locate_deleted_positions(int len) {
    delete_cnt = 0;
    int cur = head_node;
    int passed = 0; // cur 段之前所有段的总长度，即 cur 段起点在序列中的排名减 1

    for (long long x = 1; x * x * x <= len; x++) {
        int rank_pos = (int)(x * x * x);
        while (cur != 0 && passed + seg_len[cur] < rank_pos) {
            passed += seg_len[cur];
            cur = nxt[cur];
        }
        int offset = rank_pos - passed;
        delete_cnt++;
        deleted_node[delete_cnt] = cur;
        deleted_offset[delete_cnt] = offset;
        deleted_value[delete_cnt] = a[start_pos[cur] + offset - 1];
    }
}

// 按上一轮定位到的删除点，统一把受影响的段切开。
// 同一轮中一个段可能被多个删除点命中，按段分组后一次性处理。
void apply_deletions() {
    int i = 1;
    while (i <= delete_cnt) {
        int x = deleted_node[i];
        int old_start = start_pos[x];
        int old_len = seg_len[x];
        int l = pre[x];
        int r = nxt[x];

        // 收集落在段 x 内的所有删除偏移。
        vector<int> offsets;
        while (i <= delete_cnt && deleted_node[i] == x) {
            offsets.push_back(deleted_offset[i]);
            i++;
        }

        // 按偏移从小到大，把段切成若干"保留段"，中间夹着的删除点全部去掉。
        int first_new = 0;
        int last_new = 0;
        int last_cut = 0; // 上一个删除点，新的保留段从它之后开始
        for (int j = 0; j < (int)offsets.size(); j++) {
            int off = offsets[j];
            int keep_len = off - last_cut - 1;
            int node = new_node(old_start + last_cut, keep_len);
            if (node != 0) {
                if (first_new == 0) first_new = node;
                if (last_new != 0) insert_after(last_new, node);
                last_new = node;
            }
            last_cut = off;
        }
        // 最后一个删除点之后到段尾的剩余部分。
        int tail_len = old_len - last_cut;
        int tail_node = new_node(old_start + last_cut, tail_len);
        if (tail_node != 0) {
            if (first_new == 0) first_new = tail_node;
            if (last_new != 0) insert_after(last_new, tail_node);
            last_new = tail_node;
        }

        // 用新段序列替换掉链表中的旧段 x。
        if (l != 0) nxt[l] = first_new;
        else head_node = first_new;
        if (first_new != 0) pre[first_new] = l;

        if (last_new != 0) {
            nxt[last_new] = r;
            if (r != 0) pre[r] = last_new;
        }
        else {
            if (l != 0) nxt[l] = r;
            if (r != 0) pre[r] = l;
            if (l == 0) head_node = r;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    // 初始整个序列是一个段：原数组 [1, n]。
    node_cnt = 0;
    head_node = new_node(1, n);

    int len = n; // 当前剩余序列长度
    while (len > 0) {
        // 先只定位本轮删除点，再统一切开，保证"同时删除"。
        locate_deleted_positions(len);

        vector<int> values;
        for (int i = 1; i <= delete_cnt; i++) values.push_back(deleted_value[i]);
        rounds.push_back(values);

        apply_deletions();
        len -= delete_cnt;
    }

    cout << rounds.size() << '\n';
    for (int i = 0; i < (int)rounds.size(); i++) {
        for (int j = 0; j < (int)rounds[i].size(); j++) {
            if (j) cout << ' ';
            cout << rounds[i][j];
        }
        cout << '\n';
    }
    return 0;
}
