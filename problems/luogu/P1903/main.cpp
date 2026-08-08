#include <bits/stdc++.h>
using namespace std;

const int MAXN = 133335;
const int MAXV = 1000005;

struct Query {
    int l, r, t, id;
};

struct Change {
    int pos, old_color, new_color;
};

int n, m;
int block_size;
int initial_color[MAXN];
int current_color[MAXN]; // 莫队移动过程中数组当前位置的颜色。
int color_count[MAXV];   // 当前询问区间内每种颜色出现次数。
int distinct_count;
int query_count, change_count;
int answer[MAXN];
Query queries[MAXN];
Change changes[MAXN];

bool cmp_query(const Query &a, const Query &b) {
    int block_l_a = a.l / block_size;
    int block_l_b = b.l / block_size;
    if (block_l_a != block_l_b) {
        return block_l_a < block_l_b;
    }
    int block_r_a = a.r / block_size;
    int block_r_b = b.r / block_size;
    if (block_r_a != block_r_b) {
        return block_r_a < block_r_b;
    }
    return a.t < b.t;
}

void add_pos(int pos) {
    int c = current_color[pos];
    if (color_count[c] == 0) {
        distinct_count++;
    }
    color_count[c]++;
}

void remove_pos(int pos) {
    int c = current_color[pos];
    color_count[c]--;
    if (color_count[c] == 0) {
        distinct_count--;
    }
}

void apply_change(int change_id, int cur_l, int cur_r) {
    int pos = changes[change_id].pos;
    int new_color = changes[change_id].new_color;
    if (cur_l <= pos && pos <= cur_r) {
        remove_pos(pos);
        current_color[pos] = new_color;
        add_pos(pos);
    } else {
        current_color[pos] = new_color;
    }
}

void undo_change(int change_id, int cur_l, int cur_r) {
    int pos = changes[change_id].pos;
    int old_color = changes[change_id].old_color;
    if (cur_l <= pos && pos <= cur_r) {
        remove_pos(pos);
        current_color[pos] = old_color;
        add_pos(pos);
    } else {
        current_color[pos] = old_color;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> initial_color[i];
        current_color[i] = initial_color[i];
    }

    int temp_color[MAXN];
    for (int i = 1; i <= n; i++) {
        temp_color[i] = initial_color[i];
    }

    for (int i = 1; i <= m; i++) {
        char op;
        int x, y;
        cin >> op >> x >> y;
        if (op == 'Q') {
            query_count++;
            queries[query_count].l = x;
            queries[query_count].r = y;
            queries[query_count].t = change_count;
            queries[query_count].id = query_count;
        } else {
            change_count++;
            changes[change_count].pos = x;
            changes[change_count].old_color = temp_color[x];
            changes[change_count].new_color = y;
            temp_color[x] = y;
        }
    }

    block_size = max(1, (int)pow(n, 2.0 / 3.0));
    sort(queries + 1, queries + query_count + 1, cmp_query);

    int cur_l = 1, cur_r = 0, cur_t = 0;
    for (int i = 1; i <= query_count; i++) {
        while (cur_l > queries[i].l) {
            cur_l--;
            add_pos(cur_l);
        }
        while (cur_r < queries[i].r) {
            cur_r++;
            add_pos(cur_r);
        }
        while (cur_l < queries[i].l) {
            remove_pos(cur_l);
            cur_l++;
        }
        while (cur_r > queries[i].r) {
            remove_pos(cur_r);
            cur_r--;
        }

        // cur_t 表示当前数组已经应用了前 cur_t 次修改。
        while (cur_t < queries[i].t) {
            cur_t++;
            apply_change(cur_t, cur_l, cur_r);
        }
        while (cur_t > queries[i].t) {
            undo_change(cur_t, cur_l, cur_r);
            cur_t--;
        }

        answer[queries[i].id] = distinct_count;
    }

    for (int i = 1; i <= query_count; i++) {
        cout << answer[i] << '\n';
    }

    return 0;
}
