/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:34
 * update_at: 2026-10-06 14:34
 */

#include <cstdio>

typedef long long ll;

const int MAXV = 1005; // 单词大小不超过 1000

int m, n;
int word;              // 当前读入的单词
int q[MAXV];           // 内存队列：q[head] 是最早进入的单词，q[tail-1] 是最新的
int head, tail;        // 队列的队首和队尾（左闭右开）
bool in_memory[MAXV];  // in_memory[w] 表示单词 w 当前是否在内存里
ll ans;                // 查词典的总次数

int main() {
    scanf("%d %d", &m, &n);
    // M 可以为 0：此时内存永远为空，每个词都要查词典
    for (int i = 1; i <= n; i++) {
        scanf("%d", &word);
        if (in_memory[word])
            continue;            // 内存里已有，命中，不查词典
        ans++;                   // 未命中，查一次词典
        if (m > 0) {             // M=0 时存不下任何词，只计数
            if (tail - head == m) {              // 内存已满
                in_memory[q[head]] = false;      // 淘汰最早进入的单词
                head++;
            }
            q[tail] = word;      // 新单词进入内存
            tail++;
            in_memory[word] = true;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
