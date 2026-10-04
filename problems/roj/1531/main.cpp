/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:32
 * update_at: 2026-10-05 06:51
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXM = 2005; // 街最多 1995 条
const int MAXV = 60;   // 路口最多 44 个

typedef long long ll;

struct Street {
    int x, y, id; // 街连接的两个路口与街编号
};

int m;                 // 本组街数
int home_v;            // 起点：本组第一条街两端编号较小的路口
Street st[MAXM];       // 每条街的信息
vector<int> adj[MAXV]; // adj[v]：与路口 v 相连的街下标，按街编号升序
int adjlen[MAXV];      // adj[v] 的长度，避免反复取 size
int nxt_e[MAXM];       // 回路中当前街的下一条街：-1 未走过，-2 已走但还没并进回路
int prv_e[MAXM];       // 回路中当前街的上一条街
int ptr[MAXV];         // 各路口在 adj 里扫描到的位置，只增不减
int trail_head, trail_tail, stop_v; // extend_trail 的结果：首街、尾街、停住的路口
int anchor;                        // 回路首街（锚点），作退回起点的判定

// 按街编号升序排序，保证每个路口取边时也是编号升序。
bool cmp_street(const Street &a, const Street &b) {
    return a.id < b.id;
}

// 从 junction 沿没走过的街贪心延伸到走不动为止，结果存入 trail_head / trail_tail / stop_v。
void extend_trail(int junction) {
    trail_head = -1;
    trail_tail = -1;
    while (true) {
        int p = ptr[junction];
        // 跳过这条街上已经走过的街
        while (p < adjlen[junction] && nxt_e[adj[junction][p]] != -1) p++;
        ptr[junction] = p;
        if (p == adjlen[junction]) { // 这个路口再没有没走过的街，贪心停止
            stop_v = junction;
            return;
        }
        int s = adj[junction][p];
        if (trail_head == -1) { // 新路径的第一条街
            trail_head = s;
            prv_e[s] = -2;
        } else {
            prv_e[s] = trail_tail;
            nxt_e[trail_tail] = s;
        }
        nxt_e[s] = -2;
        trail_tail = s;
        // 走到街的另一端；自环两端相同，原地不动
        junction = (st[s].x == junction) ? st[s].y : st[s].x;
    }
}

// Hierholzer：构造从起点出发、经过每条街恰好一次又回到起点的回路。
// 贪心路径停在出发点以外说明存在奇数度路口，回路不存在，返回 false。
bool euler_circuit() {
    for (int v = 0; v < MAXV; v++) ptr[v] = 0;
    for (int i = 1; i <= m; i++) {
        nxt_e[i] = -1;
        prv_e[i] = -1;
    }

    extend_trail(home_v);
    if (stop_v != home_v) return false; // 停在别的路口：奇数度，回路不存在
    anchor = trail_head;               // 第一条闭合路径的首街就是回路锚点
    prv_e[anchor] = trail_tail;
    nxt_e[trail_tail] = anchor; // 首尾相接成闭合回路
    int cursor = anchor;
    int junction = home_v;
    while (true) {
        // 在当前路口反复贪心，把新走出的闭合路径插到 cursor 街前面
        while (true) {
            extend_trail(junction);
            if (stop_v != junction) return false; // 奇数度路口，回路不存在
            if (trail_head == -1) break;          // 当前路口的街已全部入回路
            int before = prv_e[cursor];
            prv_e[trail_head] = before;
            nxt_e[before] = trail_head;
            prv_e[cursor] = trail_tail;
            nxt_e[trail_tail] = cursor;
        }
        // 沿回路后退一条街：先退 cursor，再以新 cursor 街的另一端作为新路口，
        // 这样新路口正好对上 cursor 与前一条街之间的接入位置
        cursor = prv_e[cursor];
        junction = (st[cursor].x == junction) ? st[cursor].y : st[cursor].x;
        if (cursor == anchor) break; // 退回锚点街：整圈扫完，所有街都已入回路
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int x, y;
        m = 0;
        // 一组数据：若干 "x y z"，遇到带 0 的一行结束本组
        while (cin >> x >> y) {
            if (x == 0 || y == 0) break;
            int z;
            cin >> z;
            m++;
            st[m].x = x;
            st[m].y = y;
            st[m].id = z;
        }
        if (!cin || m == 0) break; // 又读到 0：整个输入结束

        home_v = min(st[1].x, st[1].y); // 起点要在排序前从输入第一条街取
        sort(st + 1, st + m + 1, cmp_street);
        for (int v = 0; v < MAXV; v++) {
            adj[v].clear();
            adjlen[v] = 0;
        }
        // 街已按编号升序，顺序挂进邻接表后每个路口的取边顺序自然也是升序
        for (int i = 1; i <= m; i++) {
            adj[st[i].x].push_back(i);
            adjlen[st[i].x]++;
            if (st[i].y != st[i].x) { // 自环只挂一次
                adj[st[i].y].push_back(i);
                adjlen[st[i].y]++;
            }
        }

        if (euler_circuit()) {
            // 从锚点街沿 nxt_e 走一圈，依次输出街编号
            int s = anchor;
            while (true) {
                cout << st[s].id;
                s = nxt_e[s];
                if (s == anchor) break;
                cout << ' ';
            }
            cout << '\n';
        } else {
            cout << "Round trip does not exist.\n";
        }
    }
    return 0;
}
