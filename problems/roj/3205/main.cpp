/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 棋盘上的骑士：二分图最大匹配，最大独立集 = 可用格子数 - 最大匹配
#include <cstdio>
#include <vector>
using namespace std;

const int STEP[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
                        {1, -2},  {1, 2},  {2, -1},  {2, 1}};

int main() {
    int n, m, T;
    if (scanf("%d %d %d", &n, &m, &T) != 3) {
        return 0;
    }
    vector<char> blocked(n * m, 0);
    int blocked_cnt = 0;
    for (int i = 0; i < T; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        if (!blocked[(x - 1) * m + y - 1]) {
            blocked[(x - 1) * m + y - 1] = 1;
            blocked_cnt++;
        }
    }

    // 左部取偶格（(r+c) 为偶），把邻接表压成 CSR
    vector<int> offset;
    vector<int> flat;
    offset.push_back(0);
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (((r + c) & 1) || blocked[r * m + c]) {
                continue;
            }
            for (int s = 0; s < 8; s++) {
                int nr = r + STEP[s][0], nc = c + STEP[s][1];
                if (nr < 0 || nr >= n || nc < 0 || nc >= m) {
                    continue;
                }
                if (blocked[nr * m + nc]) {
                    continue;
                }
                flat.push_back(nr * m + nc);
            }
            offset.push_back((int)flat.size());
        }
    }

    int size = n * m;
    vector<int> match(size, -1); // 右部格 -> 匹配到它的左部格
    vector<int> seen(size, 0);   // 右部格 -> 最后一次被访问的轮次
    int total = 0;
    int lefts = (int)offset.size() - 1;

    for (int u = 0; u < lefts; u++) { // 先做一遍贪心拿到初始匹配
        for (int i = offset[u]; i < offset[u + 1]; i++) {
            if (match[flat[i]] < 0) {
                match[flat[i]] = u;
                total++;
                break;
            }
        }
    }

    for (int round_id = 1; round_id <= lefts; round_id++) {
        int u0 = round_id - 1;
        bool already = false;
        for (int i = offset[u0]; i < offset[u0 + 1]; i++) {
            if (match[flat[i]] == u0) {
                already = true;
            }
        }
        if (already) {
            continue; // 贪心阶段已经配上
        }
        // 显式栈代替递归：帧 = (左部格, 下一个待试邻居位置, 进入它时经过的右部格)
        vector<int> su, si, svia;
        su.push_back(u0);
        si.push_back(offset[u0]);
        svia.push_back(-1);
        while (!su.empty()) {
            int u = su.back(), i = si.back();
            if (i >= offset[u + 1]) { // 所有出路都试过了，回溯
                su.pop_back();
                si.pop_back();
                svia.pop_back();
                continue;
            }
            si.back() = i + 1;
            int v = flat[i];
            if (seen[v] == round_id) {
                continue;
            }
            seen[v] = round_id;
            if (match[v] < 0) { // 撞上空闲的右部格：找到一条增广路
                match[v] = u;
                for (int t = (int)su.size() - 1; t > 0; t--) { // 路上原来的匹配边各后移一位
                    match[svia[t]] = su[t - 1];
                }
                total++;
                su.clear();
                si.clear();
                svia.clear();
                break;
            }
            su.push_back(match[v]);
            si.push_back(offset[match[v]]);
            svia.push_back(v);
        }
    }

    printf("%d\n", n * m - blocked_cnt - total);
    return 0;
}
