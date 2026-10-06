/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:31
 * update_at: 2026-10-04 22:31
 */
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <utility>
#include <cstdlib>
using namespace std;

typedef long long ll;

const int MAXN = 25;          // 网格最大行/列
const int MAXNM = 400;        // N * M <= 20 * 20
const int MAXV = MAXNM * MAXNM; // 状态数 (NM)^2
const ll INF = 1LL << 60;
const ll STEP = 1LL << 20;    // 一次推箱的代价，放在高位

// 四个方向按题目优先级 N < S < W < E（同时也是 n < s < w < e 的顺序）
const int DIRS[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const char PUSH_CH[4] = {'N', 'S', 'W', 'E'};
const char WALK_CH[4] = {'n', 's', 'w', 'e'};

int n, m, nm;                 // 当前测试用例的行列与格子数
char grid[MAXN][MAXN];        // 原始地图
bool free_cell[MAXNM];        // free_cell[id] = 该格子不是墙
ll cost[MAXV];                // cost[state] = 从该状态到终局的最小编码代价

// 把二维坐标压成一维编号
inline int id(int r, int c) { return r * m + c; }

// 判断两个格子是否相邻
inline bool adjacent(int r1, int c1, int r2, int c2) {
    int dr = r1 - r2, dc = c1 - c2;
    return dr * dr + dc * dc == 1;
}

// 反向 Dijkstra：以所有「箱子已在 T」的状态为源点，求每个状态到终局的最小代价
void backward_cost(int person_start, int box_start, int target) {
    fill(cost, cost + nm * nm, INF);
    // 小根堆，(代价, 状态)
    priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > pq;
    for (int p = 0; p < nm; ++p) {
        if (!free_cell[p]) continue;
        int state = p * nm + target;
        cost[state] = 0;
        pq.push(make_pair(0LL, state));
    }

    int start_state = person_start * nm + box_start;
    while (!pq.empty()) {
        pair<ll, int> cur = pq.top();
        pq.pop();
        ll d = cur.first;
        int state = cur.second;
        if (d != cost[state]) continue; // 过期条目
        if (state == start_state) break;  // 起点的最优值已定稿

        int person = state / nm;
        int box = state % nm;
        int pr = person / m, pc = person % m;
        int br = box / m, bc = box % m;

        // 反向的人移动：人从当前格子的某个四邻走到 person，箱子不动
        for (int i = 0; i < 4; ++i) {
            int nr = pr + DIRS[i][0];
            int nc = pc + DIRS[i][1];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            int near = id(nr, nc);
            if (!free_cell[near] || near == box) continue;
            int before = near * nm + box;
            if (d + 1 < cost[before]) {
                cost[before] = d + 1;
                pq.push(make_pair(cost[before], before));
            }
        }

        // 反向的推箱：当前状态是推完之后，人站在箱子的旧格子上
        // 推之前箱子站在 person 格，人站在 person 关于 box 的对称格
        if (adjacent(pr, pc, br, bc)) {
            int opr = 2 * pr - br;
            int opc = 2 * pc - bc;
            if (0 <= opr && opr < n && 0 <= opc && opc < m) {
                int old_person = id(opr, opc);
                if (free_cell[old_person]) {
                    int before = old_person * nm + person;
                    if (d + STEP < cost[before]) {
                        cost[before] = d + STEP;
                        pq.push(make_pair(cost[before], before));
                    }
                }
            }
        }
    }
}

// 在紧边上按优先级贪心，还原字典序最小的最优动作串
string path_of(int person, int box, int target) {
    int start_state = person * nm + box;
    ll limit = cost[start_state];
    string ans;
    ll spent = 0;

    while (box != target) {
        int pr = person / m, pc = person % m;
        int br = box / m, bc = box % m;

        bool moved = false;

        // ① 若人贴着箱子，检查唯一可能的推箱动作是否为紧边
        if (adjacent(pr, pc, br, bc)) {
            int nr = 2 * br - pr; // 箱子被推后的新格子
            int nc = 2 * bc - pc;
            if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                int new_box = id(nr, nc);
                if (free_cell[new_box]) {
                    int after_state = box * nm + new_box;
                    if (spent + STEP + cost[after_state] == limit) {
                        // 推方向 = 箱子相对于人的位置（人指向箱子的向量）
                        int dr = br - pr;
                        int dc = bc - pc;
                        int dir_idx;
                        if (dr == -1) dir_idx = 0;          // N
                        else if (dr == 1) dir_idx = 1;       // S
                        else if (dc == -1) dir_idx = 2;     // W
                        else dir_idx = 3;                   // E
                        ans.push_back(PUSH_CH[dir_idx]);
                        person = box;
                        box = new_box;
                        spent += STEP;
                        moved = true;
                    }
                }
            }
        }

        if (moved) continue;

        // ② 否则按 n、s、w、e 的顺序找第一条紧的走路边
        for (int i = 0; i < 4; ++i) {
            int nr = pr + DIRS[i][0];
            int nc = pc + DIRS[i][1];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            int next_person = id(nr, nc);
            if (!free_cell[next_person] || next_person == box) continue;
            int after_state = next_person * nm + box;
            if (spent + 1 + cost[after_state] == limit) {
                ans.push_back(WALK_CH[i]);
                person = next_person;
                spent += 1;
                moved = true;
                break;
            }
        }

        // 因为 limit 是最优代价，当前状态又满足 spent + cost[当前] == limit，
        // 所以必定存在一条紧边可以走。
        if (!moved) break;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string output;
    int case_idx = 0;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        ++case_idx;
        nm = n * m;

        int person = -1, box = -1, target = -1;
        for (int i = 0; i < n; ++i) {
            cin >> grid[i];
            for (int j = 0; j < m; ++j) {
                int cell_id = id(i, j);
                char ch = grid[i][j];
                free_cell[cell_id] = (ch != '#');
                if (ch == 'S') person = cell_id;
                else if (ch == 'B') box = cell_id;
                else if (ch == 'T') target = cell_id;
            }
        }

        output += "Maze #";
        output += to_string(case_idx);
        output += "\n";

        backward_cost(person, box, target);
        int start_state = person * nm + box;
        if (cost[start_state] >= INF) {
            output += "Impossible.\n\n";
        } else {
            string moves = path_of(person, box, target);
            output += moves;
            output += "\n\n";
        }
    }

    cout << output;
    return 0;
}
