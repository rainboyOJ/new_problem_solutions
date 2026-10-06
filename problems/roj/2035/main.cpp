// 两只塔姆沃斯牛（usaco-2.3.5 / 2035）
// 10x10 网格模拟：牛和 John 每步向前一格，撞墙/障碍则原地转向 90°。
// 两者每步最多 100 个位置 × 4 个朝向，模拟 400 步内不相遇即永不相遇。
#include <cstdio>

typedef long long ll;

const int N = 10;
const int STEPS = 400; // 位置(100)×朝向(4) 全状态只有 400 种

char g[N + 2][N + 2]; // 地图，边界设为障碍
int fx, fy, fdir;     // John 的位置与朝向
int cx, cy, cdir;     // 牛的位置与朝向

// 朝向：0 上，1 右，2 下，3 左
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

// 尝试向前走一格，撞障碍则原地转向 90°（顺时针）
void step(int &x, int &y, int &dir) {
    int nx = x + dx[dir];
    int ny = y + dy[dir];
    if (g[nx][ny] == '*') { // 前方是障碍，只转向不前进
        dir = (dir + 1) % 4;
    } else {
        x = nx;
        y = ny;
    }
}

int main() {
    // 边界设为障碍，简化越界判断
    for (int i = 0; i <= N + 1; i++) {
        g[0][i] = '*';
        g[N + 1][i] = '*';
        g[i][0] = '*';
        g[i][N + 1] = '*';
    }
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++) {
            scanf(" %c", &g[i][j]);
            if (g[i][j] == 'F') {
                fx = i;
                fy = j;
                g[i][j] = '.'; // John 离开后该格变空
            } else if (g[i][j] == 'C') {
                cx = i;
                cy = j;
                g[i][j] = '.';
            }
        }

    fdir = 0; // 都朝北出发
    cdir = 0;

    // 逐步模拟，最多 400 步（全状态数上限）
    for (int t = 1; t <= STEPS; t++) {
        step(fx, fy, fdir);
        step(cx, cy, cdir);
        if (fx == cx && fy == cy) { // 相遇
            printf("%d\n", t);
            return 0;
        }
    }
    // 400 步内未相遇，则状态进入循环，永不相遇
    printf("0\n");
    return 0;
}
