/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 21:14
 * update_at: 2026-10-08 21:47
 */
// 3072 八数码：逆序数奇偶性预判无解 + 曼哈顿距离启发式的 A* 搜索求最短操作序列。

#include <iostream>
#include <queue>
#include <string>

using namespace std;

typedef long long ll;

const ll MAX_STATE = 362880; // 9! = 362880，八数码全部可能状态数
const ll INF_DIST = -1;      // node[].dist 用 -1 表示该状态还没被搜到

// 康托展开用的阶乘表，FACT[i] = i!
const ll FACT[9] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};

const ll DR[4] = {-1, 1, 0, 0}; // 与 DIR_CH 一一对应：上、下、左、右
const ll DC[4] = {0, 0, -1, 1};
const char DIR_CH[4] = {'u', 'd', 'l', 'r'};

// 一个状态的全部附加信息合在一个 struct 里，下标就是状态的康托编码
struct Node {
    ll dist;  // 起点到该状态的最短步数，INF_DIST 表示未访问
    ll prev;  // 前驱状态的康托编码
    char op;  // 从前驱状态走到该状态的那一步（u/d/l/r）
};

Node node[MAX_STATE]; // node[code] 描述康托编码为 code 的状态

// 优先队列元素：f = 已走步数 + 曼哈顿距离估计
struct State {
    ll f;
    ll code;

    bool operator<(const State& other) const {
        return f > other.f; // priority_queue 默认大根堆，反向比较得到小根堆
    }
};

char start_board[9]; // 输入的初始局面，按行优先展开；'x' 表示空格
char cur_board[9];   // 当前取出扩展的局面
char nxt_board[9];   // 交换一步后的新局面

const char* TARGET = "12345678x"; // 正确排列，康托编码为 0

// 康托展开：把 9 个格子的排列映射成 [0, 9!) 中的下标
ll cantor_encode(const char* s) {
    ll code = 0;
    for (ll i = 0; i < 9; i++) {
        ll smaller = 0; // 第 i 位右边比 s[i] 小的字符个数
        for (ll j = i + 1; j < 9; j++) {
            if (s[j] < s[i]) smaller++;
        }
        code += smaller * FACT[8 - i];
    }
    return code;
}

// 康托展开的逆运算：由下标还原出排列
void cantor_decode(ll code, char* s) {
    ll rank[9];
    for (ll i = 0; i < 9; i++) {
        rank[i] = code / FACT[8 - i];
        code %= FACT[8 - i];
    }
    string avail = "12345678x";
    for (ll i = 0; i < 9; i++) {
        s[i] = avail[rank[i]];
        avail.erase(avail.begin() + rank[i]);
    }
}

// 曼哈顿距离：所有数字当前位置到目标位置的横纵距离之和，是可采纳的启发式
ll manhattan(const char* s) {
    ll h = 0;
    for (ll i = 0; i < 9; i++) {
        if (s[i] == 'x') continue;
        ll value = s[i] - '0'; // 数字 1~8，目标位置是 value - 1 号格子
        ll target_idx = value - 1;
        ll row_gap = i / 3 - target_idx / 3;
        ll col_gap = i % 3 - target_idx % 3;
        if (row_gap < 0) row_gap = -row_gap;
        if (col_gap < 0) col_gap = -col_gap;
        h += row_gap + col_gap;
    }
    return h;
}

// 忽略空格后剩余数字序列的逆序对个数。
// 空格左右移动不改变数字相对顺序，上下移动相当于跳过两个数字（逆序对变化 ±2 或 0），
// 所以奇偶性不变；目标态逆序对为 0（偶），故逆序对为奇数时一定无解。
ll inversions(const char* s) {
    ll inv = 0;
    for (ll i = 0; i < 9; i++) {
        if (s[i] == 'x') continue;
        for (ll j = i + 1; j < 9; j++) {
            if (s[j] == 'x') continue;
            if (s[i] > s[j]) inv++;
        }
    }
    return inv;
}

bool read_input() {
    char c;
    for (ll i = 0; i < 9; i++) {
        if (!(cin >> c)) return false; // 输入不足 9 个 token，直接退出
        if (c == 'X') c = 'x';         // 题面示例里出现过大写 X，统一成小写
        start_board[i] = c;
    }
    return true;
}

// A* 搜索：从初始局面出发，用康托编码去重，找一条到目标态的最短路径
void solve() {
    if (inversions(start_board) % 2 != 0) {
        cout << "unsolvable" << "\n";
        return;
    }

    ll start_code = cantor_encode(start_board);
    ll target_code = cantor_encode(TARGET);
    if (start_code == target_code) {
        cout << "\n"; // 已经在正确排列上，行动记录为空
        return;
    }

    for (ll i = 0; i < MAX_STATE; i++) node[i].dist = INF_DIST;

    priority_queue<State> pq;
    node[start_code].dist = 0;
    node[start_code].prev = -1;
    node[start_code].op = 0;
    State first;
    first.f = manhattan(start_board);
    first.code = start_code;
    pq.push(first);

    while (!pq.empty()) {
        State top = pq.top();
        pq.pop();
        ll cur_code = top.code;
        cantor_decode(cur_code, cur_board);
        // 惰性删除：队列里的旧记录 f 比"实际步数 + 启发值"大，说明它已过期
        if (top.f > node[cur_code].dist + manhattan(cur_board)) continue;
        if (cur_code == target_code) break;

        ll blank = 0; // 空格所在格子
        for (ll i = 0; i < 9; i++) {
            if (cur_board[i] == 'x') blank = i;
        }
        ll r = blank / 3;
        ll c = blank % 3;

        for (ll d = 0; d < 4; d++) {
            ll nr = r + DR[d];
            ll nc = c + DC[d];
            if (nr < 0 || nr > 2 || nc < 0 || nc > 2) continue;

            ll nidx = nr * 3 + nc;
            for (ll i = 0; i < 9; i++) nxt_board[i] = cur_board[i];
            char t = nxt_board[blank];
            nxt_board[blank] = nxt_board[nidx];
            nxt_board[nidx] = t;

            ll next_code = cantor_encode(nxt_board);
            ll new_dist = node[cur_code].dist + 1;
            if (node[next_code].dist == INF_DIST || new_dist < node[next_code].dist) {
                node[next_code].dist = new_dist;
                node[next_code].prev = cur_code;
                node[next_code].op = DIR_CH[d];
                State ns;
                ns.f = new_dist + manhattan(nxt_board);
                ns.code = next_code;
                pq.push(ns);
            }
        }
    }

    // 从目标态沿前驱倒推，得到正向的操作序列
    string ans = "";
    ll cur = target_code;
    while (cur != start_code) {
        ans += node[cur].op;
        cur = node[cur].prev;
    }
    // 双指针原地反转字符串
    ll len = ans.size();
    for (ll i = 0; i < len / 2; i++) {
        char t = ans[i];
        ans[i] = ans[len - 1 - i];
        ans[len - 1 - i] = t;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!read_input()) return 0;
    solve();

    return 0;
}
