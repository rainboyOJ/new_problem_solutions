/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:15
 * update_at: 2026-10-06 16:15
 */
// 内存分配：逐事件模拟（时间跨度最大 1e9，不能逐时间格推进）。
// 核心结构：
//   1. blocks：地址升序的空闲块表（map<首地址, 长度>），first-fit 取首地址最小的可容纳块；
//   2. occupied：按结束时刻的小根堆，堆顶就是下一个要归还内存的进程；
//   3. 等待队列：FIFO，只有队头会被尝试分配，其它成员不得插队。
// 同一时刻的处理顺序（由样例 12/2 反推）：先释放 -> 再派发队头 -> 最后处理到达。
// 注意：新到达的进程可以越过放不下的队头直接分配（队头约束只作用于队列内部）。

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;

typedef long long ll;

int n; // 进程个数（不含结束标志 0 0 0）

ll total_n; // 总内存单元数 N

struct Proc {
    ll t; // 申请时刻
    ll m; // 需要的内存单元数
    ll p; // 运行时间
};
Proc procs[MAXN];

map<ll, ll> blocks; // 空闲块表：首地址 -> 长度，按键升序，保证 first-fit 首地址最小

// 释放堆：按 (结束时刻, 首地址, 长度) 排序的小根堆
priority_queue< pair<ll, pair<ll, ll> >,
               vector< pair<ll, pair<ll, ll> > >,
               greater< pair<ll, pair<ll, ll> > > > occupied;

ll wait_q[MAXN]; // 等待队列，存进程下标
int qhead, qtail;

// 在空闲块表中分配 need 个单元：沿地址序扫第一个长度 >= need 的块，
// 从块前端切走 need 个单元，余量留在原地；失败返回 -1。
ll alloc(ll need) {
    for (map<ll, ll>::iterator it = blocks.begin(); it != blocks.end(); it++) {
        if (it->second >= need) {
            ll start = it->first;
            ll rest = it->second - need;
            blocks.erase(it);
            if (rest > 0) blocks[start + need] = rest;
            return start;
        }
    }
    return -1;
}

// 归还 [start, start+len)：插回空闲块表，并与恰好首尾相接的左右邻居合并。
void release(ll start, ll len) {
    // 先试右邻：右邻首地址恰好等于本块尾地址
    map<ll, ll>::iterator rit = blocks.find(start + len);
    if (rit != blocks.end()) {
        len += rit->second;
        blocks.erase(rit);
    }
    // 再试左邻：左邻尾地址恰好等于本块首地址
    map<ll, ll>::iterator lit = blocks.lower_bound(start);
    if (lit != blocks.begin()) {
        lit--;
        if (lit->first + lit->second == start) {
            lit->second += len; // 直接把本块并入左邻，无需新插入
            return;
        }
    }
    blocks[start] = len;
}

void read_input() {
    cin >> total_n;
    n = 0;
    ll t, m, p;
    while (cin >> t >> m >> p) {
        if (t == 0 && m == 0 && p == 0) break;
        n++;
        procs[n].t = t;
        procs[n].m = m;
        procs[n].p = p;
    }
}

void solve() {
    // 初始时整段内存 [0, N) 是一个空闲块
    blocks[0] = total_n;

    ll now = 0;    // 当前事件时刻，也是最后的全部运行完毕时刻
    ll idx = 1;    // 下一个待处理到达的进程下标（数据按 T 升序）
    ll queued = 0; // 进过等待队列的进程总数

    while (idx <= n || !occupied.empty()) {
        // 下一事件时刻 = min(下一次到达时刻, 堆顶最早释放时刻)
        ll t_arr = (idx <= n) ? procs[idx].t : LLONG_MAX;
        ll t_rel = occupied.empty() ? LLONG_MAX : occupied.top().first;
        now = min(t_arr, t_rel);

        // 第 1 步：释放所有结束时刻 == now 的进程（先释放，队头才能用上刚归还的内存）
        while (!occupied.empty() && occupied.top().first == now) {
            release(occupied.top().second.first, occupied.top().second.second);
            occupied.pop();
        }

        // 第 2 步：反复尝试派发队头，放不下立即停止；队列内部不得插队
        while (qhead < qtail) {
            ll id = wait_q[qhead];
            ll start = alloc(procs[id].m);
            if (start == -1) break;
            qhead++;
            occupied.push(make_pair(now + procs[id].p, make_pair(start, procs[id].m)));
        }

        // 第 3 步：处理这一时刻的到达；到达者可越过放不下的队头，失败才入队并计数
        while (idx <= n && procs[idx].t == now) {
            ll start = alloc(procs[idx].m);
            if (start != -1) {
                occupied.push(make_pair(now + procs[idx].p, make_pair(start, procs[idx].m)));
            } else {
                queued++;
                wait_q[qtail++] = idx;
            }
            idx++;
        }
    }

    cout << now << "\n" << queued << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
