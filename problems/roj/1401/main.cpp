/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:53
 * update_at: 2026-10-05 12:53
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXM = 105;

int m, n;
int q[MAXM];      // 队列：按进入顺序存放内存中的单词，队首为最旧
int head, tail;   // 队首、队尾指针（[head, tail)）
int inq[1005];    // inq[x] = 1 表示单词 x 当前在内存中（单词值不超过 1000）

// 判断单词 w 是否在内存中
bool find(int w) {
    return inq[w];
}

// 将单词 w 调入内存：若已满则淘汰队首最早进入的单词
void insert(int w) {
    if (tail - head == m) {   // 内存已满
        inq[q[head]] = 0;     // 淘汰队首
        head++;
    }
    q[tail++] = w;            // 新单词入队尾
    inq[w] = 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int w;
        cin >> w;
        if (find(w)) continue; // 内存命中，直接翻译
        ans++;                  // 未命中：查一次外存词典
        insert(w);              // 调入内存
    }
    cout << ans << "\n";
    return 0;
}
