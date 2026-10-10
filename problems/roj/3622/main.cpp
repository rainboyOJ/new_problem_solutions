#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int n;
int initial_grid[5][7];

struct Move {
    int x, y, g;
} ans[10];

// 方块下落逻辑：让每一列悬空的方块落到底部
void fall(int g[5][7]) {
    for (int x = 0; x < 5; ++x) {
        int ptr = 0;
        for (int y = 0; y < 7; ++y) {
            if (g[x][y] != 0) {
                g[x][ptr++] = g[x][y];
            }
        }
        for (int y = ptr; y < 7; ++y) {
            g[x][y] = 0;
        }
    }
}

// 消除连续 >= 3 的同色方块
bool clear_blocks(int g[5][7]) {
    bool to_clear[5][7] = {false};
    bool any_clear = false;
    for (int x = 0; x < 5; ++x) {
        for (int y = 0; y < 7; ++y) {
            if (g[x][y] != 0) {
                int val = g[x][y];
                // 水平检测
                if (x - 1 >= 0 && x + 1 < 5 && g[x-1][y] == val && g[x+1][y] == val) {
                    to_clear[x-1][y] = to_clear[x][y] = to_clear[x+1][y] = true;
                    any_clear = true;
                }
                // 垂直检测
                if (y - 1 >= 0 && y + 1 < 7 && g[x][y-1] == val && g[x][y+1] == val) {
                    to_clear[x][y-1] = to_clear[x][y] = to_clear[x][y+1] = true;
                    any_clear = true;
                }
            }
        }
    }
    if (!any_clear) return false;
    for (int x = 0; x < 5; ++x) {
        for (int y = 0; y < 7; ++y) {
            if (to_clear[x][y]) {
                g[x][y] = 0;
            }
        }
    }
    return true;
}

// 掉落与消除循环，直到稳定
void process(int g[5][7]) {
    fall(g);
    while (clear_blocks(g)) {
        fall(g);
    }
}

// 深度优先搜索
bool dfs(int step, int g[5][7]) {
    if (step == n) {
        // 检查是否全部消除完
        for (int x = 0; x < 5; ++x) {
            if (g[x][0] != 0) return false;
        }
        return true;
    }
    
    // 剪枝1：如果某种颜色的方块只剩 1 个或 2 个，绝对不可能消除，直接剪枝
    int cnt[11] = {0};
    for (int x = 0; x < 5; ++x) {
        for (int y = 0; y < 7; ++y) {
            if (g[x][y] != 0) {
                cnt[g[x][y]]++;
            }
        }
    }
    for (int i = 1; i <= 10; ++i) {
        if (cnt[i] == 1 || cnt[i] == 2) return false;
    }
    
    int next_g[5][7];
    for (int x = 0; x < 5; ++x) {
        for (int y = 0; y < 7; ++y) {
            if (g[x][y] == 0) continue;
            
            // 剪枝及移动优先级1：优先向右移动 (字典序要求 x 小、g=1 优先)
            if (x + 1 < 5) {
                if (g[x][y] != g[x+1][y]) { // 剪枝：颜色相同交换无意义
                    memcpy(next_g, g, sizeof(next_g));
                    swap(next_g[x][y], next_g[x+1][y]);
                    process(next_g);
                    ans[step] = {x, y, 1};
                    if (dfs(step + 1, next_g)) return true;
                }
            }
            
            // 剪枝及移动优先级2：向左移动 (当且仅当左侧为空时才移动)
            // 如果左侧有方块，将其向左移动等效于将其左侧的方块向右移动，而后者字典序更优！
            if (x - 1 >= 0 && g[x-1][y] == 0) {
                memcpy(next_g, g, sizeof(next_g));
                swap(next_g[x][y], next_g[x-1][y]);
                process(next_g);
                ans[step] = {x, y, -1};
                if (dfs(step + 1, next_g)) return true;
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    if (!(cin >> n)) return 0;
    
    memset(initial_grid, 0, sizeof(initial_grid));
    for (int x = 0; x < 5; ++x) {
        int y = 0;
        int val;
        while (cin >> val && val != 0) {
            initial_grid[x][y++] = val;
        }
    }
    
    if (dfs(0, initial_grid)) {
        for (int i = 0; i < n; ++i) {
            cout << ans[i].x << " " << ans[i].y << " " << ans[i].g << "\n";
        }
    } else {
        cout << "-1\n";
    }
    
    return 0;
}