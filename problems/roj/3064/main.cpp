/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 09:00
 * update_at: 2026-10-09 11:34
 */

#include <cstring>
#include <iostream>
#include <string>

using namespace std;

typedef long long ll;

// 16×16 数独转精确覆盖：4096 个决策行、1024 个约束列，DLX 求解。
const int MAX_ROW = 4100;   // 候选决策行数上界：16×16×16 = 4096，留一点余量
const int MAX_COL = 1030;   // 约束列数上界：4×256 = 1024，加上总表头
const int MAX_NODE = 20000; // 十字链表节点数上界：1024 个头 + 4096×4 个数据节点

// DLX 十字链表的一个节点：数据节点和列头节点共用同一套数组，
// 列头节点的 up/down/left/right 指向自身，size 记录该列当前的数据节点个数。
struct Node {
    int up;     // 上邻居编号
    int down;   // 下邻居编号
    int left;   // 左邻居编号
    int right;  // 右邻居编号
    int col;    // 所属约束列编号（列头节点就是自己）
    int row;    // 所属决策行编号，只有数据节点有意义
    int size;   // 该列的数据节点个数，只有列头节点会用到
};

Node node[MAX_NODE];      // node 0..m 是列头（含总表头 m），m+1 起是数据节点
int head[MAX_ROW];        // head[r] = 第 r 个决策行横向环的第一个节点，-1 表示该行还没有节点
int chosen[MAX_ROW];      // chosen[d] = 搜索第 d 层时选中的决策行编号
int chosen_cnt;           // 已选中的决策行个数
int node_cnt;             // 已经开出的节点个数，也是下一个可用下标
char grid[16][17];        // 当前谜面，解决后被原地填满

// 初始化 0..m 号列头节点与总表头，并清空每行表头
void init(int m) {
    for (int i = 0; i <= m; i++) {
        node[i].left = i - 1;
        node[i].right = i + 1;
        node[i].up = i;
        node[i].down = i;
        node[i].col = i;
        node[i].size = 0;
    }
    node[0].left = m;
    node[m].right = 0;
    node_cnt = m;
    memset(head, -1, sizeof(head));
}

// 把「决策行 r 覆盖约束列 c」这条边插到 c 列底部、并接进 r 行的横向环
void link(int r, int c) {
    node_cnt++;
    node[node_cnt].col = c;
    node[node_cnt].row = r;
    node[c].size++;

    node[node_cnt].up = node[c].up;
    node[node_cnt].down = c;
    node[node[c].up].down = node_cnt;
    node[c].up = node_cnt;

    if (head[r] == -1) {
        head[r] = node_cnt;
        node[node_cnt].left = node_cnt;
        node[node_cnt].right = node_cnt;
    } else {
        node[node_cnt].left = node[head[r]].left;
        node[node[head[r]].left].right = node_cnt;
        node[node_cnt].right = head[r];
        node[head[r]].left = node_cnt;
    }
}

// 从列环里摘掉列头 c，并把 c 列每行从它的其他列里一并删除
void cover(int c) {
    node[node[c].right].left = node[c].left;
    node[node[c].left].right = node[c].right;
    for (int i = node[c].down; i != c; i = node[i].down) {
        for (int j = node[i].right; j != i; j = node[j].right) {
            node[node[j].down].up = node[j].up;
            node[node[j].up].down = node[j].down;
            node[node[j].col].size--;
        }
    }
}

// cover 的逆操作，必须严格按被删除的相反顺序恢复
void uncover(int c) {
    for (int i = node[c].up; i != c; i = node[i].up) {
        for (int j = node[i].left; j != i; j = node[j].left) {
            node[node[j].down].up = j;
            node[node[j].up].down = j;
            node[node[j].col].size++;
        }
    }
    node[node[c].right].left = c;
    node[node[c].left].right = c;
}

// 第 d 层的选择：挑当前 size 最小的列来分支（最小列启发式）
bool dfs(int d) {
    if (node[0].right == 0) { // 所有约束列都被精确覆盖了
        chosen_cnt = d;
        return true;
    }
    int c = node[0].right;
    for (int i = node[0].right; i != 0; i = node[i].right) {
        if (node[i].size < node[c].size) {
            c = i;
        }
    }

    cover(c);
    for (int i = node[c].down; i != c; i = node[i].down) {
        chosen[d] = node[i].row;
        for (int j = node[i].right; j != i; j = node[j].right) {
            cover(node[j].col);
        }
        if (dfs(d + 1)) {
            return true;
        }
        for (int j = node[i].left; j != i; j = node[j].left) {
            uncover(node[j].col);
        }
    }
    uncover(c);
    return false;
}

// 把 16×16 数独建成精确覆盖模型：每格一个候选字母是一行，覆盖 4 个约束列
void build_grid() {
    init(1024);
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            for (int k = 0; k < 16; k++) {
                // 谜面已固定成别的字母时，这一格填 k 的决策直接丢弃
                if (grid[i][j] != '-' && grid[i][j] != 'A' + k) {
                    continue;
                }
                int r = i * 256 + j * 16 + k + 1;
                int c1 = i * 16 + j + 1;             // 约束 1：格子 (i,j) 只能填一个字母
                int c2 = 256 + i * 16 + k + 1;       // 约束 2：第 i 行必须出现字母 k
                int c3 = 512 + j * 16 + k + 1;       // 约束 3：第 j 列必须出现字母 k
                int b = (i / 4) * 4 + (j / 4);
                int c4 = 768 + b * 16 + k + 1;       // 约束 4：第 b 个十六宫格必须出现字母 k

                link(r, c1);
                link(r, c2);
                link(r, c3);
                link(r, c4);
            }
        }
    }
}

// 把解出的决策行还原成字母写回 grid
void fill_answer() {
    for (int i = 0; i < chosen_cnt; i++) {
        int r = chosen[i] - 1;
        int k = r % 16;
        r /= 16;
        int j = r % 16;
        r /= 16;
        grid[r][j] = 'A' + k;
    }
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            cout << grid[i][j];
        }
        cout << "\n";
    }
    cout << "\n"; // 题面要求：每个测试用例输出结束后再输出一个空行
}

// 逐组读入谜面（组间空行由 cin >> 自动跳过），读到 EOF 为止
void solve() {
    string s;
    while (cin >> s) {
        for (int j = 0; j < 16; j++) {
            grid[0][j] = s[j];
        }
        for (int i = 1; i < 16; i++) {
            cin >> s;
            for (int j = 0; j < 16; j++) {
                grid[i][j] = s[j];
            }
        }

        build_grid();
        if (dfs(0)) {
            fill_answer();
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
