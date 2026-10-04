/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:54
 * update_at: 2026-10-05 06:54
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXK = 11;
const int MAXE = 1 << MAXK; // 边数最多 2^11 = 2048

typedef long long ll;

// de Bruijn 图：节点是 K-1 位 01 串，边是 K 位 01 串。
// 节点 u 追加标号 b 后走到 ((u << 1) | b) 的后 K-1 位。
// 边编号 e = (u << 1) | b 恰好就是该 K 位串的整数值，所以直接用 e 标记边。

ll K;
ll mask;                  // 只保留低 K-1 位的掩码
bool edge_used[MAXE];     // edge_used[e] 表示长度 K 的 01 串 e 是否已经被用过
ll stack_node[MAXE];      // Hierholzer 显式栈：栈顶节点的 K-1 位编号
int stack_entry[MAXE];    // 进入该节点时走过的边标号（只有 0/1），起点记为 -1
int emit[MAXE];           // 后序记录的边标号，逆序才是欧拉回路的走向
char circuit[MAXE];       // 欧拉回路的边标号序列，即环上的 01 串
char ring[MAXE];          // 旋转到全 0 子串开头后的最终方案

// 迭代式 Hierholzer：每个节点先试 0 边再试 1 边，出边耗尽才回溯。
void build_circuit() {
    ll top = 0;
    stack_node[0] = 0;
    stack_entry[0] = -1;

    ll emit_cnt = 0;
    while (top >= 0) {
        ll u = stack_node[top];
        bool moved = false;

        for (int b = 0; b <= 1; b++) {
            ll e = (u << 1) | b;
            if (!edge_used[e]) {
                edge_used[e] = true;
                top++;
                stack_node[top] = e & mask;
                stack_entry[top] = b;
                moved = true;
                break;
            }
        }

        if (!moved) {
            int entry = stack_entry[top];
            top--;
            if (entry >= 0) {
                emit[emit_cnt] = entry;
                emit_cnt++;
            }
        }
    }

    // emit 是后序记录，逆序即为回路经过各边的顺序。
    for (ll i = 0; i < emit_cnt; i++) {
        circuit[i] = '0' + emit[emit_cnt - 1 - i];
    }
    circuit[emit_cnt] = '\0';
}

// 把回路旋转到唯一的 0^K 子串处开头，得到字典序最小的方案。
void rotate_to_all_zero() {
    ll len = 1LL << K;
    ll head = -1;

    for (ll i = 0; i < len && head < 0; i++) {
        bool all_zero = true;
        for (ll j = 0; j < K; j++) {
            if (circuit[(i + j) % len] != '0') {
                all_zero = false;
                break;
            }
        }
        if (all_zero) {
            head = i;
        }
    }

    for (ll i = 0; i < len; i++) {
        ring[i] = circuit[(head + i) % len];
    }
    ring[len] = '\0';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> K;
    mask = (1LL << (K - 1)) - 1;

    build_circuit();
    rotate_to_all_zero();

    cout << (1LL << K) << ' ' << ring << '\n';

    return 0;
}
