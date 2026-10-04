/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:51
 * update_at: 2026-10-04 22:51
 */

// 牛半仙的魔塔：树上「父亲先于儿子」的块合并贪心。
// 单场战斗的代价是勇士挨打 t = ceil(b/(A-d)) - 1 次，收益是 val 级升级（防御 +val），
// 于是每场战斗的性价比 rho = val / t；父亲必须先打的限制用并查集把「攒着的子块」
// 并进父亲块（新块的 rho 是按挨打次数加权平均），大根堆每次弹出全局 rho 最大的块。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

typedef long long ll;

int n;
vector<int> g[MAXN]; // g[u] 存节点 u 的所有邻居

ll hp, hero_atk, armor; // 勇士初始血量、攻击、盔甲防御
ll monster_atk[MAXN];   // monster_atk[u] 节点 u 魔物的攻击
ll hits[MAXN];          // hits[u] 打死节点 u 的魔物前，勇士要挨的攻击次数
ll gain[MAXN];          // gain[u] 打死节点 u 的魔物后提升的等级（也是防御增量）
int up[MAXN];           // up[u] 节点 u 在树上的父亲，根 1 的父亲为 0

int block_top[MAXN];           // 并查集：指向所在块的块顶
ll block_gain[MAXN];           // 块内累计升级
ll block_hits[MAXN];           // 块内累计挨打次数
vector<int> merged_kids[MAXN]; // merged_kids[x] 已并入块顶 x 的子块，按并入先后排列
int ver[MAXN];                 // 块顶的版本号，用来丢掉堆里的过期键
int scheduled[MAXN];           // 是否已出战（起点 1 视为最先出战）
int order_list[MAXN];          // 最终的出战顺序
int order_cnt;
int work_stack[MAXN]; // 迭代遍历树、展开整块时共用的显式栈

// 堆元素：块的性价比 = block_gain / block_hits，block_hits 为 0 时视为无穷大。
struct BlockNode {
    ll gain_v;
    ll hits_v;
    int id;     // 块顶编号
    int ticket; // 该块顶的版本号，只有等于 ver[id] 的键才有效
};

// priority_queue 默认大根堆，operator< 定义「性价比更小」的一方为更小。
bool operator<(const BlockNode &x, const BlockNode &y) {
    if (x.hits_v == 0 || y.hits_v == 0) {
        if (x.hits_v == 0 && y.hits_v == 0) {
            return x.id < y.id; // 两块都是一击必杀，顺序随意，用编号定序
        }
        return y.hits_v == 0; // x 的性价比有限、y 的无穷大，则 x 更小
    }
    return x.gain_v * y.hits_v < y.gain_v * x.hits_v; // 交叉相乘比较，避免浮点误差
}

priority_queue<BlockNode> heap;

// 并查集查块顶，带路径压缩。
int find_top(int x) {
    while (block_top[x] != x) {
        block_top[x] = block_top[block_top[x]];
        x = block_top[x];
    }
    return x;
}

// 把块顶 u 的当前信息压进堆，并升级它的版本号。
void push_block(int u) {
    ver[u]++;
    BlockNode node;
    node.gain_v = block_gain[u];
    node.hits_v = block_hits[u];
    node.id = u;
    node.ticket = ver[u];
    heap.push(node);
}

void read_input() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    cin >> hp >> hero_atk >> armor;

    // 怪物第 k 行对应节点 k + 1，依次是血量 b、攻击 a、防御 d、提升等级 v
    for (int u = 2; u <= n; u++) {
        ll b, a, d, v;
        cin >> b >> a >> d >> v;
        monster_atk[u] = a;
        gain[u] = v;
        // 勇士先手，打死共需 ceil(b/(A-d)) 击，此前只挨 k - 1 次反击
        ll per_hit = hero_atk - d;
        hits[u] = (b + per_hit - 1) / per_hit - 1;
    }
}

// 以 1 为根，用显式栈做迭代 DFS 求出每个点的父亲。
void build_parent() {
    for (int i = 1; i <= n; i++) {
        up[i] = 0;
    }
    int top = 0;
    work_stack[top++] = 1;
    up[1] = -1; // 先占位表示根已访问，遍历完再还原成 0
    while (top > 0) {
        int u = work_stack[--top];
        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (up[v] == 0) {
                up[v] = u;
                work_stack[top++] = v;
            }
        }
    }
    up[1] = 0;
}

void solve() {
    for (int i = 1; i <= n; i++) {
        block_top[i] = i;
        block_gain[i] = gain[i];
        block_hits[i] = hits[i];
    }
    scheduled[1] = 1; // 1 号点是起点，没有魔物，视为最先出战
    for (int u = 2; u <= n; u++) {
        push_block(u);
    }

    while (!heap.empty()) {
        BlockNode cur = heap.top();
        heap.pop();
        if (cur.ticket != ver[cur.id]) {
            continue; // 过期键：该块顶后来并过新子块，已压入新版本
        }
        int u = cur.id;
        if (scheduled[up[u]]) {
            // 父亲已出战：整个块立刻出战，块顶最先，子块按并入先后（性价比降序）出战
            int top = 0;
            work_stack[top++] = u;
            while (top > 0) {
                int x = work_stack[--top];
                scheduled[x] = 1;
                order_list[order_cnt++] = x;
                // 逆序压栈，保证先并入的子块先弹出
                for (int i = (int)merged_kids[x].size() - 1; i >= 0; i--) {
                    work_stack[top++] = merged_kids[x][i];
                }
            }
        } else {
            // 父亲还没上场：整块并进父亲所在的块攒着，性价比取按挨打次数的加权平均
            int p = find_top(up[u]);
            block_gain[p] += block_gain[u];
            block_hits[p] += block_hits[u];
            merged_kids[p].push_back(u);
            block_top[u] = p;
            push_block(p);
        }
    }

    // 按出战顺序结算血量；中途死亡输出 -1
    ll cur_hp = hp;
    ll defense = armor;
    for (int i = 0; i < order_cnt; i++) {
        int u = order_list[i];
        cur_hp -= hits[u] * (monster_atk[u] - defense);
        if (cur_hp <= 0) {
            cout << -1 << "\n";
            return;
        }
        defense += gain[u];
    }
    cout << cur_hp << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    build_parent();
    solve();

    return 0;
}
