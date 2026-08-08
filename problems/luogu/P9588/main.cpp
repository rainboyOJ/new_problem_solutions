#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const int MAXQ = 200000 + 5;

struct Block {
    i64 len;    // 原始长度 x
    i64 start;  // 当前已经弹掉了多少个前缀元素，剩下的是 [start+1 .. len]

    i64 size() const {
        return len - start;
    }

    i64 max_value() const {
        return len;
    }

    i64 kth(i64 k) const {
        return start + k;
    }
};

int q;
vector<Block> blocks;
int head_ptr = 0;
i64 prefix_size[MAXQ];

void rebuild_prefix() {
    i64 sum = 0;
    for (int i = head_ptr; i < (int)blocks.size(); i++) {
        sum += blocks[i].size();
        prefix_size[i] = sum;
    }
}

int find_block_by_rank(i64 z) {
    int left = head_ptr;
    int right = (int)blocks.size() - 1;
    int ans = right;

    while (left <= right) {
        int mid = (left + right) >> 1;
        if (prefix_size[mid] >= z) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long ignored_n;
    cin >> ignored_n >> q;

    for (int i = 1; i <= q; i++) {
        int op;
        cin >> op;

        if (op == 1) {
            i64 x;
            cin >> x;
            blocks.push_back({x, 0});
        } else if (op == 2) {
            i64 y;
            cin >> y;

            while (y > 0) {
                i64 cur_size = blocks[head_ptr].size();
                if (cur_size <= y) {
                    y -= cur_size;
                    head_ptr++;
                } else {
                    blocks[head_ptr].start += y;
                    y = 0;
                }
            }
        } else if (op == 3) {
            i64 z;
            cin >> z;

            rebuild_prefix();
            int idx = find_block_by_rank(z);
            i64 prev = (idx == head_ptr ? 0 : prefix_size[idx - 1]);
            i64 inside_rank = z - prev;
            cout << blocks[idx].kth(inside_rank) << '\n';
        } else {
            i64 answer = 0;
            for (int j = head_ptr; j < (int)blocks.size(); j++) {
                if (blocks[j].size() > 0) {
                    answer = max(answer, blocks[j].max_value());
                }
            }
            cout << answer << '\n';
        }
    }

    return 0;
}
