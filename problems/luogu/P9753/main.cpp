/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:36
 * update_at: 2026-11-10 20:13
 */
// main.cpp：消除栈的双哈希统计可消除子串。
// 两个前缀消除后的栈状态相同时，其中间子串可被完全消除。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int MAXN = 2000005; // n <= 2e6

// 双哈希基数与模数，防止哈希碰撞
const ull BASE1 = 13331ULL;
const ull BASE2 = 23333ULL;
const ull MOD2 = 1000000007ULL;

int n;
string s;

// 消除栈字符与历史哈希快照
char stack_char[MAXN];
ull hash1_history[MAXN];
ull hash2_history[MAXN];
int stack_top;

// 记录所有前缀消除栈哈希状态的扁平结构，用于排序统计
ull packed_hash[MAXN];

// 求解函数：主解基于哈希栈，时间复杂度 O(n log n)，空间 O(n)
ll solve_hash_stack() {
    stack_top = 0;
    hash1_history[0] = 0;
    hash2_history[0] = 0;

    // 前缀 0（空串）对应的消除栈哈希为 0
    packed_hash[0] = 0;

    for (int i = 0; i < n; i++) {
        char c = s[i];
        if (stack_top > 0 && stack_char[stack_top] == c) {
            // 栈顶字符与当前字符相同，两者消去，弹栈回退到上一历史哈希
            stack_top--;
        } else {
            // 无法消除，新字符压栈并更新滚动哈希
            stack_top++;
            stack_char[stack_top] = c;
            hash1_history[stack_top] = hash1_history[stack_top - 1] * BASE1 + static_cast<ull>(c);
            hash2_history[stack_top] = (hash2_history[stack_top - 1] * BASE2 + static_cast<ull>(c)) % MOD2;
        }

        // 把 64 位自然溢出哈希与 32 位模哈希打包成一个 64 位整型（高 32 位为 hash2，低 32 位为 hash1 的低 32 位）
        ull combined = (hash2_history[stack_top] << 32) ^ hash1_history[stack_top];
        packed_hash[i + 1] = combined;
    }

    // 排序统计每个哈希值的出现次数 cnt，答案为 sum(cnt * (cnt - 1) / 2)
    sort(packed_hash, packed_hash + n + 1);

    ll answer = 0;
    ll current_count = 1;
    for (int i = 1; i <= n; i++) {
        if (packed_hash[i] == packed_hash[i - 1]) {
            current_count++;
        } else {
            answer += current_count * (current_count - 1) / 2;
            current_count = 1;
        }
    }
    answer += current_count * (current_count - 1) / 2;

    return answer;
}

/*
// -------------------------------------------------------------
// 对照解法：Trie 树状态图转移法（O(n * 26) 时间，空间较大）
// 每个结点代表一个“消除栈状态”，结点 0 表示空栈。
// parent_node[u]：状态 u 去掉栈顶字符之后的状态；
// node_char[u]：状态 u 的栈顶字符（只有非根结点才有意义）。
int parent_node[MAXN];
char node_char[MAXN];
int first_edge[MAXN], to_node[MAXN], next_edge[MAXN];
int node_cnt, edge_cnt;
ll seen_count[MAXN];

int get_child(int u, char c) {
    for (int e = first_edge[u]; e != 0; e = next_edge[e]) {
        int v = to_node[e];
        if (node_char[v] == c) return v;
    }
    node_cnt++;
    parent_node[node_cnt] = u;
    node_char[node_cnt] = c;
    edge_cnt++;
    to_node[edge_cnt] = node_cnt;
    next_edge[edge_cnt] = first_edge[u];
    first_edge[u] = edge_cnt;
    return node_cnt;
}

ll solve_trie() {
    ll answer = 0;
    int cur = 0;
    seen_count[0] = 1;
    for (int i = 0; i < n; i++) {
        char c = s[i];
        if (cur != 0 && node_char[cur] == c) {
            cur = parent_node[cur];
        } else {
            cur = get_child(cur, c);
        }
        answer += seen_count[cur];
        seen_count[cur]++;
    }
    return answer;
}
// -------------------------------------------------------------
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s;

    cout << solve_hash_stack() << '\n';

    return 0;
}
