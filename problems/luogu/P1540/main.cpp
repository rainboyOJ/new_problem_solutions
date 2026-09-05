/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-05 09:50
 * update_at: 2026-09-05 09:50
 */
#include <bits/stdc++.h>
using namespace std;

int m, n;   // m 内存容量, n 文章单词数
int cnt;    // 查词典的次数
queue<int> q;       // 内存中单词的进入顺序(FIFO)
bool in_memory[1005]; // 桶: 单词 x 当前是否在内存中

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;

    for (int i = 1; i <= n; i++) {
        int x; // 当前要翻译的单词
        cin >> x;

        // 内存中已有该单词, 直接翻译, 不查词典
        if (in_memory[x]) {
            continue;
        }

        cnt++; // 需要去外存查词典

        // 内存已满: 清掉最早进入内存的单词, 腾出单元
        if ((int) q.size() == m) {
            int oldest = q.front();
            q.pop();
            in_memory[oldest] = false;
        }

        // 新单词放入内存, 并记录进入顺序
        q.push(x);
        in_memory[x] = true;
    }

    cout << cnt << '\n';
    return 0;
}
