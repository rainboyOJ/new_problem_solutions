/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 17:40
 * update_at: 2026-10-06 17:40
 */
// 玛雅游戏：恰好 n 步清空棋盘，输出字典序最小的移动序列，无解输出 -1。
// 做法：按 x、y、右移优先的顺序 DFS，遇到第一个解即为最小字典序；配合
// 四条剪枝（同色空转、左移交换、颜色计数不足 3、失败局面记忆化）压缩搜索树。
#include <cstring>
#include <iostream>
#include <set>
#include <string>
using namespace std;

typedef long long ll;

const int W = 5; // 棋盘列数
const int H = 7; // 棋盘行数

int n;                 // 要求恰好移动的步数
int a[W][H];           // a[x][y] 为第 x 列自下而上第 y 个方块的颜色，仅 y < h[x] 有效
int h[W];              // h[x] 为第 x 列当前方块数
bool dead[W][H];       // dead[x][y] 标记本轮该被消除的方块

int ans_x[64];         // 第 i 步移动的列
int ans_y[64];         // 第 i 步移动的行
int ans_g[64];         // 第 i 步移动的方向

set<string> failed;    // 记录「该局面 + 剩余步数」已确认无解，避免重复搜索

// 把当前局面和剩余步数编码成可哈希的字符串，用作记忆化的键。
string encode_state(int left) {
    string s;
    s.push_back(char(left));
    for (int x = 0; x < W; x++) {
        for (int y = 0; y < h[x]; y++) {
            s.push_back(char(a[x][y]));
        }
        s.push_back(char(0)); // 用 0 分隔各列
    }
    return s;
}

// 扫描所有行和列，把本轮该消除的方块整体标记在 dead 上；无三连返回 false。
bool mark_dead() {
    memset(dead, 0, sizeof(dead));
    bool found = false;
    // 竖向三连
    for (int x = 0; x < W; x++) {
        for (int y = 0; y + 2 < h[x]; y++) {
            if (a[x][y] == a[x][y + 1] && a[x][y + 1] == a[x][y + 2]) {
                found = true;
                dead[x][y] = dead[x][y + 1] = dead[x][y + 2] = true;
            }
        }
    }
    // 横向三连，不足 7 格的列把缺位读作颜色 0（颜色从 1 开始，0 不会凑成三连）
    for (int y = 0; y < H; y++) {
        for (int x = 0; x + 2 < W; x++) {
            int c0 = (y < h[x]) ? a[x][y] : 0;
            int c1 = (y < h[x + 1]) ? a[x + 1][y] : 0;
            int c2 = (y < h[x + 2]) ? a[x + 2][y] : 0;
            if (c0 != 0 && c0 == c1 && c1 == c2) {
                found = true;
                dead[x][y] = dead[x + 1][y] = dead[x + 2][y] = true;
            }
        }
    }
    return found;
}

// 消除与掉落的循环：整体标记删除后压实，掉落过程不判定消除，直到局面稳定。
void settle() {
    while (mark_dead()) {
        for (int x = 0; x < W; x++) {
            int w = 0;
            for (int y = 0; y < h[x]; y++) {
                if (!dead[x][y]) {
                    a[x][w] = a[x][y];
                    w++;
                }
            }
            h[x] = w;
        }
    }
}

// 把第 x 列第 y 个方块沿 g 方向拖动一格；无意义移动返回 false。
bool apply_move(int x, int y, int g) {
    int nx = x + g;
    if (nx < 0 || nx >= W) return false;
    if (y < h[nx]) { // 目标位置有方块：交换
        if (a[nx][y] == a[x][y]) return false; // 同色交换后局面不变，白走一步
        int tmp = a[nx][y];
        a[nx][y] = a[x][y];
        a[x][y] = tmp;
    } else { // 目标位置为空：从原列抽出并落向目标列顶部
        int v = a[x][y];
        for (int k = y; k + 1 < h[x]; k++) a[x][k] = a[x][k + 1];
        h[x]--;
        int p = (y < h[nx]) ? y : h[nx]; // 落点不会高于目标列当前高度
        for (int k = h[nx]; k > p; k--) a[nx][k] = a[nx][k - 1];
        a[nx][p] = v;
        h[nx]++;
    }
    settle();
    return true;
}

// 还剩 left 步时能否把棋盘清空；枚举顺序保证第一个解就是字典序最小的解。
bool dfs(int left) {
    string key = encode_state(left);
    if (failed.count(key)) return false;
    if (left == 0) { // 恰好 n 步走完，检查是否清空
        for (int x = 0; x < W; x++) {
            if (h[x] > 0) return false;
        }
        return true;
    }
    int cnt[11] = {0}; // 颜色 1~10 的方块计数
    for (int x = 0; x < W; x++) {
        for (int y = 0; y < h[x]; y++) {
            cnt[a[x][y]]++;
        }
    }
    for (int c = 1; c <= 10; c++) {
        if (cnt[c] > 0 && cnt[c] < 3) { // 某颜色只剩 1~2 块，永远凑不出三连，必败
            failed.insert(key);
            return false;
        }
    }
    for (int x = 0; x < W; x++) {
        for (int y = 0; y < h[x]; y++) {
            for (int gi = 0; gi < 2; gi++) { // 先右移后左移，字典序更小的先枚举
                int g = (gi == 0) ? 1 : -1;
                int nx = x + g;
                if (nx < 0 || nx >= W) continue;
                // 左移交换等于左邻方块右移，而后者字典序更小且已被枚举过，剪掉
                if (g == -1 && y < h[nx]) continue;
                // 备份当前局面，试走一步后递归，失败再还原
                int sa[W][H];
                int sh[W];
                for (int i = 0; i < W; i++) {
                    sh[i] = h[i];
                    for (int j = 0; j < h[i]; j++) sa[i][j] = a[i][j];
                }
                if (apply_move(x, y, g)) {
                    ans_x[n - left] = x;
                    ans_y[n - left] = y;
                    ans_g[n - left] = g;
                    if (dfs(left - 1)) return true;
                }
                for (int i = 0; i < W; i++) {
                    h[i] = sh[i];
                    for (int j = 0; j < sh[i]; j++) a[i][j] = sa[i][j];
                }
            }
        }
    }
    failed.insert(key);
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int x = 0; x < W; x++) {
        int v;
        cin >> v;
        while (v != 0) {
            a[x][h[x]] = v;
            h[x]++;
            cin >> v;
        }
    }
    if (dfs(n)) {
        for (int i = 0; i < n; i++) {
            cout << ans_x[i] << " " << ans_y[i] << " " << ans_g[i] << "\n";
        }
    } else {
        cout << -1 << "\n";
    }
    return 0;
}
