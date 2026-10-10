/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 木板：横木板与竖木板建二分图，König 定理下最小点覆盖 = 最大匹配
#include <cstdio>
#include <vector>
using namespace std;

struct Frame { // 匈牙利算法的显式栈帧
    int v; // 当前纵向木板
    int i; // 下一个待试邻居下标
    int x; // 最近想抢的横向木板
};

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) {
        return 0;
    }
    vector<vector<char> > grid(n, vector<char>(m + 1));
    for (int i = 0; i < n; i++) {
        scanf("%s", &grid[i][0]);
    }

    // 横向切分：每格所属横向木板编号（干净格为 -1）
    vector<vector<int> > rows(n, vector<int>(m, -1));
    int row_cnt = 0;
    for (int i = 0; i < n; i++) {
        int seg = -1;
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '.') {
                seg = -1;
            } else {
                if (seg < 0) {
                    seg = row_cnt++;
                }
            }
            rows[i][j] = seg;
        }
    }

    // 纵向木板 → 它压住的横向木板编号列表
    vector<vector<int> > groups;
    for (int c = 0; c < m; c++) {
        int r = 0;
        while (r < n) {
            if (grid[r][c] == '.') {
                r++;
                continue;
            }
            int start = r;
            while (r < n && grid[r][c] == '*') {
                r++;
            }
            vector<int> cur;
            for (int i = start; i < r; i++) {
                cur.push_back(rows[i][c]);
            }
            groups.push_back(cur);
        }
    }

    // 匈牙利：每个纵向段沿「横向段已配的纵向段」下潜找增广路
    vector<int> match(row_cnt, -1);
    vector<char> seen(row_cnt, 0);
    int total = 0;
    for (int v0 = 0; v0 < (int)groups.size(); v0++) {
        for (int i = 0; i < row_cnt; i++) {
            seen[i] = 0;
        }
        vector<Frame> stk;
        Frame first = {v0, 0, -1};
        stk.push_back(first);
        while (!stk.empty()) {
            Frame& fr = stk.back();
            if (fr.i == (int)groups[fr.v].size()) { // 所有出路都试过了，回溯
                stk.pop_back();
                continue;
            }
            int x = groups[fr.v][fr.i];
            fr.i++;
            fr.x = x;
            if (seen[x]) {
                continue;
            }
            seen[x] = 1;
            if (match[x] < 0) { // 撞上空闲横向木板：交替路上每个纵向段各拿一段
                for (int t = (int)stk.size() - 1; t >= 0; t--) {
                    match[stk[t].x] = stk[t].v;
                }
                total++;
                stk.clear();
                break;
            }
            Frame nf = {match[x], 0, x};
            stk.push_back(nf);
        }
    }
    printf("%d\n", total);
    return 0;
}
