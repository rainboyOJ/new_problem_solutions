#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

const int MAXM = 1e5 + 5;
const int MAX_NODES = MAXM * 40; // 每次修改最多开 O(log V) 个点

int N, M;
int front_pos, back_pos; // 预留坐标轴的前后指针
int max_pos; // 坐标轴右端点

// ==============================================================================
// 模块一：绝对坐标系下的动态开点线段树 (Absolute Coordinate Segment Tree)
// ==============================================================================

struct SegTree {
    int ls[MAX_NODES], rs[MAX_NODES];
    int sum[MAX_NODES]; // 记录区间内当前存在的真实人数
    int root, tot;

    // 核心魔法：计算任意区间 [l, r] 在“未受到任何操作时”的初始人数
    // 因为一开始所有人都在 [M + 1, M + N] 这个区间内，取交集即可。
    int default_sum(int l, int r) {
        int valid_L = max(l, M + 1);
        int valid_R = min(r, M + N);
        return valid_L <= valid_R ? (valid_R - valid_L + 1) : 0;
    }

    // 向上更新信息
    void push_up(int p, int l, int r) {
        int mid = (l + r) >> 1;
        // 如果左子树存在，取左子树的值；如果不存在，用纯数学公式计算初始值
        int left_val = ls[p] ? sum[ls[p]] : default_sum(l, mid);
        int right_val = rs[p] ? sum[rs[p]] : default_sum(mid + 1, r);
        sum[p] = left_val + right_val;
    }

    // 单点修改：将坐标 pos 处的人数改为 val (1 表示有人，0 表示没人)
    void update(int &p, int l, int r, int pos, int val) {
        // 如果来到一个全新的节点，先给它分配物理内存，并赋予初始默认状态
        if (!p) {
            p = ++tot;
            sum[p] = default_sum(l, r);
        }
        // 触底，修改叶子节点
        if (l == r) {
            sum[p] = val;
            return;
        }
        
        int mid = (l + r) >> 1;
        if (pos <= mid) update(ls[p], l, mid, pos, val);
        else update(rs[p], mid + 1, r, pos, val);
        
        push_up(p, l, r);
    }

    // 查询前缀和：查询坐标轴 [1, pos] 区间内一共有多少人（即该坐标的当前名次 Rank）
    int query_rank(int p, int l, int r, int pos) {
        // 如果节点不存在，说明这片区域处于“处女地”状态，直接用公式 $O(1)$ 结算
        if (!p) return default_sum(max(l, 1), min(r, pos));
        
        if (l == r) return sum[p]; // 触底返回
        
        int mid = (l + r) >> 1;
        if (pos <= mid) {
            return query_rank(ls[p], l, mid, pos);
        } else {
            // 如果跨越了左半区，左半区全拿，去右半区继续找
            int left_val = ls[p] ? sum[ls[p]] : default_sum(l, mid);
            return left_val + query_rank(rs[p], mid + 1, r, pos);
        }
    }

    // 线段树上二分：查找当前排在第 K 位的人所在的绝对坐标
    int query_kth(int p, int l, int r, int k) {
        if (l == r) return l; // 找到了目标坐标
        
        int mid = (l + r) >> 1;
        int left_val = ls[p] ? sum[ls[p]] : default_sum(l, mid);
        
        if (k <= left_val) {
            // 左边人数够，继续去左子树找
            return query_kth(ls[p], l, mid, k);
        } else {
            // 左边不够，减去左边的人数，去右子树找
            return query_kth(rs[p], mid + 1, r, k - left_val);
        }
    }
} tree;

// ==============================================================================
// 模块二：离散数学集合划分 —— Map 动态撕裂机制 (Interval Refinement)
// ==============================================================================

struct Interval {
    int L, R;
    int start_pos; // 这个区间内，L 所对应的绝对坐标
};

// 逻辑系统：维护 用户ID(L) -> 物理区间信息(R, start_pos) 的映射 (Bijection)
map<int, Interval> id_map; 
// 反向映射：为了操作4（查名次），需要 绝对坐标(start_pos) -> 用户ID 的映射
map<int, int> pos_map; 

// 核心函数：找到包含目标 id 的区间，如果它在中间，就“撕裂”它，并返回该 id 的绝对坐标
int split_and_get_pos(int id) {
    auto it = id_map.upper_bound(id);
    --it; // 找到对应的代表元（区间左端点）
    
    int L = it->second.L;
    int R = it->second.R;
    int pos = it->second.start_pos;
    
    // 计算目标 id 在本区间内的相对偏移量
    int target_pos = pos + (id - L); 
    
    // 如果它不是独立的单点区间，触发集合的撕裂 (Refinement)
    if (L != R) {
        id_map.erase(it);
        pos_map.erase(pos);
        
        // 拆分出左半段 [L, id-1]
        if (L <= id - 1) {
            id_map[L] = {L, id - 1, pos};
            pos_map[pos] = L;
        }
        // 拆分出右半段 [id+1, R]
        if (id + 1 <= R) {
            id_map[id + 1] = {id + 1, R, target_pos + 1};
            pos_map[target_pos + 1] = id + 1;
        }
        // 剥离出独立单点 [id, id]
        id_map[id] = {id, id, target_pos};
        pos_map[target_pos] = id;
    }
    
    return target_pos; // 返回目标在坐标轴上的绝对位置
}

// 已知 pos 处有人，查询这个绝对坐标对应的用户编号
int get_id_by_pos(int pos) {
    map<int, int>::iterator it = pos_map.upper_bound(pos);
    --it;
    return it->second + pos - it->first;
}

// 将已经被 split 成单点的用户移动到新位置
void move_user(int id, int old_pos, int new_pos) {
    tree.update(tree.root, 1, max_pos, old_pos, 0);
    tree.update(tree.root, 1, max_pos, new_pos, 1);

    id_map[id] = {id, id, new_pos};
    pos_map.erase(old_pos);
    pos_map[new_pos] = id;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;

    // 初始用户占据 [M + 1, M + N]，两端各预留 M 个位置给移动操作。
    front_pos = M + 1;
    back_pos = M + N;
    max_pos = N + 2 * M;

    id_map[1] = {1, N, M + 1};
    pos_map[M + 1] = 1;

    int last_answer = 0;
    for (int i = 1; i <= M; i++) {
        int op, x, y;
        cin >> op >> x;
        x -= last_answer;

        if (op == 1) {
            cin >> y;
            y -= last_answer;

            int pos = split_and_get_pos(x);
            last_answer = tree.query_rank(tree.root, 1, max_pos, pos);

            // x 此时已经是独立单点，直接把该单点的编号改成 y。
            id_map.erase(x);
            id_map[y] = {y, y, pos};
            pos_map[pos] = y;
        } else if (op == 2) {
            int pos = split_and_get_pos(x);
            last_answer = tree.query_rank(tree.root, 1, max_pos, pos);

            front_pos--;
            move_user(x, pos, front_pos);
        } else if (op == 3) {
            int pos = split_and_get_pos(x);
            last_answer = tree.query_rank(tree.root, 1, max_pos, pos);

            back_pos++;
            move_user(x, pos, back_pos);
        } else {
            int pos = tree.query_kth(tree.root, 1, max_pos, x);
            last_answer = get_id_by_pos(pos);
        }

        cout << last_answer << '\n';
    }

    return 0;
}
