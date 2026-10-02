/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:33
 * update_at: 2026-10-01 22:33
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;
const int MAXNODE = 300005;

int n, m, max_k, base_size;
int ability[MAXN];             // ability[i]：选手 i 的能力值，值域 [0, 2^31)，int 足够
int query_c[MAXN];             // query_c[i]：第 i 个询问的前缀长度
int draw_side[MAXNODE];       // 内部结点抽到 0/1，0 表示左边为擂主
int log_floor_value[MAXNODE]; // 堆编号的 floor(log2)
int fixed_winner[MAXNODE];    // 子树完全确定时，赢家的能力值
int free_time[MAXNODE];       // 子树最后仍可能自由变化的前缀时刻
int father_need[MAXNODE];     // 从当前结点往上，选手作为擂主需要满足的最高轮次
int known_limit[MAXNODE];     // 已知选手能力能通过的祖先限制
int front_limit[MAXNODE];     // 从上往下 DP 得到的可贡献前缀上界
ll answer_prefix[MAXN + 5];  // answer_prefix[c]：前缀 c 的可能冠军编号和（差分后缀和）

// 预处理堆编号的 log 与 father_need：沿着抽签路线，记录选手当擂主要满足的层级限制。
void prepare_tree_info() {
    base_size = 1 << max_k;

    for (int i = 2; i < base_size * 2; i++) {
        log_floor_value[i] = log_floor_value[i >> 1] + 1;
    }

    father_need[1] = max_k;
    for (int i = 2; i < base_size * 2; i++) {
        int parent = i >> 1;
        int is_right_child = i & 1;

        // 如果这个孩子所在的半区是擂主，记录跳到这里后还需要满足的层级限制。
        if (is_right_child == draw_side[parent]) {
            father_need[i] = max_k - log_floor_value[i];
        } else {
            father_need[i] = father_need[parent];
        }
    }
}

// 自底向上求 fixed_winner 与 free_time：子树完全确定时的赢家，
// 以及子树最后仍可能受补充选手影响的前缀时刻。
void build_fixed_winner() {
    for (int pos = 1; pos <= base_size; pos++) {
        int node = base_size + pos - 1;
        if (pos <= n) {
            // 已知选手在前缀达到自己之前还不可用。
            free_time[node] = pos - 1;
            fixed_winner[node] = ability[pos];
        } else {
            // 补充选手的能力可任选，一直自由。
            free_time[node] = base_size;
            fixed_winner[node] = 0;
        }
    }

    for (int pos = 1; pos <= n; pos++) {
        int node = base_size + pos - 1;
        int climb = ability[pos] < max_k ? ability[pos] : max_k;
        known_limit[node] = father_need[node >> climb];
    }

    for (int node = base_size - 1; node >= 1; node--) {
        int left = node << 1;
        int right = left | 1;
        int round_id = max_k - log_floor_value[node];

        if (draw_side[node] == 0) {
            if (fixed_winner[left] < round_id) {
                free_time[node] = free_time[right];
                fixed_winner[node] = fixed_winner[right];
            } else {
                free_time[node] = free_time[left];
                fixed_winner[node] = fixed_winner[left];
            }
        } else {
            // 右边是擂主。自由性来自右边擂主是否能跨过当前轮，所以始终继承右子树的自由时刻。
            free_time[node] = free_time[right];
            if (fixed_winner[right] >= round_id) {
                fixed_winner[node] = fixed_winner[right];
            } else {
                fixed_winner[node] = fixed_winner[left];
            }
        }
    }
}

// 对当前能力值求所有询问的答案：枚举补齐规模 W，
// 用 front_limit 把每个叶子能成为冠军的前缀区间加到差分数组上。
void solve_current_abilities() {
    for (int i = 0; i <= n + 2; i++) {
        answer_prefix[i] = 0;
    }

    build_fixed_winner();

    // W 表示当前前缀补齐到 2^W 人。
    for (int W = 0; W <= max_k; W++) {
        int lower_bound_prefix = (W == 0) ? 0 : (1 << (W - 1));
        int root_offset = (1 << (max_k - W)) - 1;

        front_limit[root_offset + 1] = base_size;

        for (int id = 1; id < (1 << W); id++) {
            int node = (root_offset << log_floor_value[id]) + id;
            int left = node << 1;
            int right = left | 1;
            int round_id = max_k - log_floor_value[node];

            front_limit[left] = front_limit[node];
            front_limit[right] = front_limit[node];

            if (draw_side[node] == 0) {
                if (fixed_winner[left] >= round_id) {
                    front_limit[right] = min(front_limit[right], free_time[node]);
                } else {
                    front_limit[left] = min(front_limit[left], free_time[left]);
                }
            } else {
                if (fixed_winner[right] >= round_id) {
                    front_limit[left] = min(front_limit[left], free_time[node]);
                } else {
                    front_limit[right] = min(front_limit[right], free_time[right]);
                }
            }
        }

        for (int i = 0; i < (1 << W); i++) {
            int player_id = i + 1;
            int leaf = base_size + i;

            // 已知选手成为冠军的前缀区间。
            if (player_id <= n && known_limit[leaf] >= W && front_limit[leaf] >= player_id &&
                front_limit[leaf] >= lower_bound_prefix + 1) {
                int left = max(player_id, lower_bound_prefix + 1);
                int right = min(front_limit[leaf], 1 << W);
                if (left <= right && left <= n) {
                    right = min(right, n);
                    answer_prefix[left] += player_id;
                    answer_prefix[right + 1] -= player_id;
                }
            }

            // 补充选手成为冠军的前缀区间。
            if (W > 0 && i > lower_bound_prefix && front_limit[leaf] >= lower_bound_prefix) {
                int left = lower_bound_prefix + 1;
                int right = min(i, front_limit[leaf]);
                if (left <= right && left <= n) {
                    right = min(right, n);
                    answer_prefix[left] += player_id;
                    answer_prefix[right + 1] -= player_id;
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        answer_prefix[i] += answer_prefix[i - 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    while ((1 << max_k) < n) {
        max_k++;
    }
    base_size = 1 << max_k;

    for (int i = 1; i <= n; i++) {
        cin >> ability[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> query_c[i];
    }

    for (int round_id = 1; round_id <= max_k; round_id++) {
        string s;
        cin >> s;
        int start = 1 << (max_k - round_id);
        for (int j = 0; j < (int)s.size(); j++) {
            draw_side[start + j] = s[j] - '0';
        }
    }

    prepare_tree_info();

    int test_count;
    cin >> test_count;
    while (test_count--) {
        int mask_value[4];
        for (int i = 0; i < 4; i++) {
            cin >> mask_value[i];
        }

        for (int i = 1; i <= n; i++) {
            ability[i] ^= mask_value[i & 3];
        }

        solve_current_abilities();

        ll ans = 0;
        for (int i = 1; i <= m; i++) {
            ans ^= 1LL * i * answer_prefix[query_c[i]];
        }

        for (int i = 1; i <= n; i++) {
            ability[i] ^= mask_value[i & 3];
        }

        cout << ans << '\n';
    }

    return 0;
}
