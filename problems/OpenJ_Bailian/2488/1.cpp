#include <iostream>
#include <cstring>

using namespace std;

// 全局变量定义
int P, Q;               // P 为行数(1..p), Q 为列数(A..q)
bool visited[30][30];    // 标记是否访问过
struct Node {
    int x, y;           // 存储路径坐标
} path[30];

// 核心：方向数组必须按照字典序排列
// 规则：优先尝试字母小的(dx小)，字母相同时尝试数字小的(dy小)
// 字母偏移 dx: -2, -2, -1, -1,  1,  1,  2,  2
// 数字偏移 dy: -1,  1, -2,  2, -2,  2, -1,  1
int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};

bool finished = false;

/**
 * DFS 搜索函数
 * @param currX 当前列坐标 (对应字母)
 * @param currY 当前行坐标 (对应数字)
 * @param step  当前步数
 */
void dfs(int currX, int currY, int step) {
    path[step].x = currX;
    path[step].y = currY;

    if (step == P * Q) {
        finished = true;
        return;
    }

    for (int i = 0; i < 8; ++i) {
        int nextX = currX + dx[i];
        int nextY = currY + dy[i];

        // 检查边界及访问情况
        if (nextX >= 1 && nextX <= Q && nextY >= 1 && nextY <= P && !visited[nextY][nextX] && !finished) {
            visited[nextY][nextX] = true;
            dfs(nextX, nextY, step + 1);
            // 回溯
            if (!finished) {
                visited[nextY][nextX] = false;
            }
        }
    }
}

void solve(int caseNum) {
    cin >> P >> Q;
    
    // 初始化
    memset(visited, false, sizeof(visited));
    finished = false;

    // 字典序最小路径必然从 A1 (1, 1) 开始
    visited[1][1] = true;
    dfs(1, 1, 1);

    cout << "Scenario #" << caseNum << ":" << endl;
    if (finished) {
        for (int i = 1; i <= P * Q; ++i) {
            // 将数字坐标转回字母和数字形式
            // path[i].x 为列(字母), path[i].y 为行(数字)
            char col = (char)(path[i].x + 'A' - 1);
            cout << col << path[i].y;
        }
        cout << endl;
    } else {
        cout << "impossible" << endl;
    }
    cout << endl; // 每个测试用例后跟一个空行
}

int main() {
    int n;
    if (!(cin >> n)) return 0;
    for (int i = 1; i <= n; ++i) {
        solve(i);
    }
    return 0;
}
