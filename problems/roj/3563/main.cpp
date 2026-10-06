/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:05
 * update_at: 2026-10-06 14:05
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXM = 55;
const int MAXN = 55;

// 单个积木的 7x6 字形，以锚点 (dy=0,dx=0) 为前面左下角
// 每行: dy 偏移, dx 起始偏移, 字符串
struct GlyphRow {
    int dy;
    int dx;
    const char *s;
};

const GlyphRow GLYPH[6] = {
    {-5, 2, "+---+"},   // 上面后沿
    {-4, 1, "/   /|"},  // 上面
    {-3, 0, "+---+ |"}, // 前面上沿 + 右面上半
    {-2, 0, "|   | +"}, // 前面 + 右面
    {-1, 0, "|   |/"},  // 前面 + 右面下斜
    {0,  0, "+---+"},   // 前面下沿
};

// 展开成 36 个落笔点，方便直接覆盖
struct Cell {
    int dy;
    int dx;
    char ch;
};
Cell cube[36];
int cube_cnt = 0;

int m, n;
int h[MAXM][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 展开字形到 cube[]
    for (int r = 0; r < 6; ++r) {
        int dy = GLYPH[r].dy;
        int dx0 = GLYPH[r].dx;
        const char *s = GLYPH[r].s;
        for (int k = 0; s[k]; ++k) {
            cube[cube_cnt].dy = dy;
            cube[cube_cnt].dx = dx0 + k;
            cube[cube_cnt].ch = s[k];
            ++cube_cnt;
        }
    }

    if (!(cin >> m >> n)) return 0;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cin >> h[i][j];

    // 画布包络尺寸
    int width = 4 * (n - 1) + 2 * (m - 1) + 7;
    int rows = 0;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            rows = max(rows, 3 * h[i][j] + 2 * (m - 1 - i));
    rows += 3; // 顶行到锚点还需 3 行余量

    // 画布，背景用 '.'
    vector<string> canvas(rows, string(width, '.'));

    // 画家算法：后排->前排，左->右，下层->上层
    for (int i = 0; i < m; ++i) {
        int depth = 2 * (m - 1 - i);          // 行 i 相对前排的后移量
        int base_y = rows - 1 - depth;        // 该行最下层锚点行
        for (int j = 0; j < n; ++j) {
            int base_x = 4 * j + depth;       // 锚点列
            for (int k = 0; k < h[i][j]; ++k) {
                int y = base_y - 3 * k;       // 第 k 层锚点行
                for (int c = 0; c < cube_cnt; ++c) {
                    int rr = y + cube[c].dy;
                    int cc = base_x + cube[c].dx;
                    canvas[rr][cc] = cube[c].ch;
                }
            }
        }
    }

    for (int i = 0; i < rows; ++i)
        cout << canvas[i] << "\n";
    return 0;
}
