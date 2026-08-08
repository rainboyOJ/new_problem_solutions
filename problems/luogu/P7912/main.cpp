#include <bits/stdc++.h>
using namespace std;

const int maxn = 200000 + 5;

int n;
int a[maxn];
int nxt_pos[maxn];
int head_pos[maxn], tail_pos[maxn], block_val[maxn];
vector<int> cur_blocks, next_blocks;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int block_cnt = 0;
    for (int i = 1; i <= n; ) {
        int j = i;
        while (j + 1 <= n && a[j + 1] == a[i]) {
            j++;
        }
        block_cnt++;
        head_pos[block_cnt] = i;
        tail_pos[block_cnt] = j;
        block_val[block_cnt] = a[i];
        for (int p = i; p < j; p++) {
            nxt_pos[p] = p + 1;
        }
        nxt_pos[j] = 0;
        cur_blocks.push_back(block_cnt);
        i = j + 1;
    }

    while (!cur_blocks.empty()) {
        next_blocks.clear();

        for (int id : cur_blocks) {
            int x = head_pos[id];
            cout << x << ' ';

            head_pos[id] = nxt_pos[x];
            if (head_pos[id] == 0) {
                continue;
            }

            if (!next_blocks.empty() && block_val[next_blocks.back()] == block_val[id]) {
                int last = next_blocks.back();
                nxt_pos[tail_pos[last]] = head_pos[id];
                tail_pos[last] = tail_pos[id];
            } else {
                next_blocks.push_back(id);
            }
        }

        cout << '\n';
        cur_blocks.swap(next_blocks);
    }

    return 0;
}
