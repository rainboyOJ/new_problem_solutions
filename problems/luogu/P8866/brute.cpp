/**
 * Problem: luogu P8866 - [NOIP2022] 喵了个喵 (Validator Simulator)
 * Author: rainboy
 * Date: 2026-11-10 23:45
 * Description: 运行 main 的核心逻辑并模拟栈操作检验是否全部消空
 */
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

// 引入 main 的算法并在内部用 deque 严格模拟
const int MAXN = 305;
const int MAXM = 2000005;
const int MAXK = 605;

int n, m, k;
int a[MAXM];
int up_pos[MAXK], down_pos[MAXK];
int val[MAXN][2];
int sz[MAXN];
int sta[MAXN];

struct Operation {
    int type;
    int s1, s2;
};

vector<Operation> ops;

bool solve_and_verify() {
    if (!(cin >> n >> m >> k)) return false;
    for (int i = 1; i <= m; ++i) {
        cin >> a[i];
    }

    ops.clear();
    for (int i = 1; i <= k; ++i) {
        up_pos[i] = down_pos[i] = 0;
    }
    for (int i = 1; i <= n; ++i) {
        val[i][0] = val[i][1] = 0;
        sz[i] = 0;
        sta[i] = 0;
    }

    vector<int> free_stacks;
    for (int i = 1; i < n; ++i) {
        free_stacks.push_back(i);
    }
    int empty_stack = n;

    for (int l = 1, r = 0; l <= m; l = r + 1) {
        r = l;
        int cur = a[l];

        if (down_pos[cur]) {
            int u = down_pos[cur];
            ops.push_back({1, empty_stack, 0});
            ops.push_back({2, u, empty_stack});
            if (sz[u] == 2) {
                int top_val = val[u][1];
                val[u][0] = top_val;
                val[u][1] = 0;
                sz[u] = 1;
                up_pos[top_val] = 0;
                down_pos[top_val] = u;
                free_stacks.push_back(u);
            } else {
                val[u][0] = 0;
                sz[u] = 0;
            }
            down_pos[cur] = 0;
        } else if (up_pos[cur]) {
            int u = up_pos[cur];
            ops.push_back({1, u, 0});
            up_pos[cur] = 0;
            sz[u] = 1;
            val[u][1] = 0;
            free_stacks.push_back(u);
        } else if (!free_stacks.empty()) {
            int u = free_stacks.back();
            free_stacks.pop_back();
            ops.push_back({1, u, 0});
            if (sz[u] == 0) {
                val[u][0] = cur;
                sz[u] = 1;
                down_pos[cur] = u;
                free_stacks.push_back(u);
            } else {
                val[u][1] = cur;
                sz[u] = 2;
                up_pos[cur] = u;
            }
        } else {
            while (r + 1 <= m) {
                r++;
                if (a[r] == cur) {
                    ops.push_back({1, empty_stack, 0});
                    for (int x = l + 1; x < r; ++x) {
                        ops.push_back({1, up_pos[a[x]], 0});
                    }
                    for (int x = l + 1; x < r; ++x) {
                        if (up_pos[a[x]] && sta[up_pos[a[x]]]) {
                            int u = up_pos[a[x]];
                            sta[u] = 0;
                            val[u][1] = 0;
                            up_pos[a[x]] = 0;
                            sz[u] = 1;
                            free_stacks.push_back(u);
                        }
                    }
                    ops.push_back({1, empty_stack, 0});
                    break;
                }
                if (down_pos[a[r]]) {
                    int u = down_pos[a[r]];
                    if (sta[u]) {
                        ops.push_back({1, empty_stack, 0});
                    } else {
                        ops.push_back({1, u, 0});
                    }

                    for (int x = l + 1; x < r; ++x) {
                        ops.push_back({1, up_pos[a[x]], 0});
                    }
                    for (int x = l + 1; x < r; ++x) {
                        if (up_pos[a[x]] && sta[up_pos[a[x]]] && up_pos[a[x]] != u) {
                            int stk = up_pos[a[x]];
                            sta[stk] = 0;
                            val[stk][1] = 0;
                            up_pos[a[x]] = 0;
                            sz[stk] = 1;
                            free_stacks.push_back(stk);
                        }
                    }

                    if (sta[u]) {
                        ops.push_back({1, u, 0});
                        sta[u] = 0;
                        down_pos[val[u][0]] = up_pos[val[u][1]] = 0;
                        val[u][0] = val[u][1] = 0;
                        sz[u] = 0;

                        down_pos[cur] = empty_stack;
                        val[empty_stack][0] = cur;
                        sz[empty_stack] = 1;
                        free_stacks.push_back(empty_stack);
                        empty_stack = u;
                    } else {
                        ops.push_back({1, empty_stack, 0});
                        ops.push_back({2, u, empty_stack});

                        down_pos[val[u][0]] = 0;
                        up_pos[val[u][1]] = 0;
                        down_pos[val[u][1]] = u;
                        up_pos[cur] = u;

                        val[u][0] = val[u][1];
                        val[u][1] = cur;
                        sz[u] = 2;
                    }
                    break;
                }
                sta[up_pos[a[r]]] ^= 1;
            }
        }
    }

    // 接下来使用真实 deque 进行物理模拟验证
    vector<deque<int>> stks(n + 1);
    int card_idx = 1;
    for (const auto &op : ops) {
        if (op.type == 1) {
            int s = op.s1;
            int card = a[card_idx++];
            if (!stks[s].empty() && stks[s].back() == card) {
                stks[s].pop_back();
            } else {
                stks[s].push_back(card);
            }
        } else {
            int s1 = op.s1;
            int s2 = op.s2;
            if (stks[s1].empty() || stks[s2].empty() || stks[s1].front() != stks[s2].front()) {
                return false; // 非法栈底消除
            }
            stks[s1].pop_front();
            stks[s2].pop_front();
        }
    }

    // 检查牌堆是否刚好用完
    if (card_idx != m + 1) return false;
    // 检查所有栈是否全空
    for (int i = 1; i <= n; ++i) {
        if (!stks[i].empty()) return false;
    }
    // 检查操作步数是否在 m 到 2m 之间
    if (ops.size() < static_cast<size_t>(m) || ops.size() > static_cast<size_t>(2 * m)) {
        return false;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        bool all_valid = true;
        while (t--) {
            if (!solve_and_verify()) {
                all_valid = false;
            }
        }
        if (all_valid) {
            cout << "ALL_VALID\n";
        } else {
            cout << "INVALID_SIMULATION\n";
        }
    }
    return 0;
}
