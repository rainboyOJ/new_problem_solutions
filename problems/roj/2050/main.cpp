/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:53
 * update_at: 2026-10-06 09:53
 */
// main.cpp：BFS 求魔板从基本状态到目标状态的最短、字典序最小操作序列。
#include <iostream>
#include <map>
#include <queue>
#include <string>

typedef long long ll;

// 三种操作在顺时针序列上的下标重排：新序列第 i 位取自旧序列 OPS[op][i] 位
const int OPS[3][8] = {
    {7, 6, 5, 4, 3, 2, 1, 0}, // A：交换上下两行，序列整体翻转
    {3, 0, 1, 2, 5, 6, 7, 4}, // B：最右一列插入最左列
    {0, 6, 1, 3, 4, 2, 5, 7}  // C：中央 2x2 顺时针旋转
};
const int POW9[8] = {1, 9, 81, 729, 6561, 59049, 531441, 4782969}; // 9 进制各位权值

std::map<int, int> prev_state; // prev_state[状态] = 前驱状态编码，基本状态记为 -1
std::map<int, char> prev_op;   // prev_op[状态] = 到达该状态所用的操作字母
std::queue<int> bfs_queue;     // BFS 队列，元素为状态编码

// 把 8 位排列编码成 9 进制整数。每一位是 1~8、不含 0，所以编码唯一。
int encode(const int s[8]) {
    int code = 0;
    for (int i = 0; i < 8; i++) {
        code += s[i] * POW9[i];
    }
    return code;
}

// 把 9 进制编码还原成 8 位排列 s。
void decode(int code, int s[8]) {
    for (int i = 0; i < 8; i++) {
        s[i] = code % 9;
        code /= 9;
    }
}

int main() {
    int target[8];
    for (int i = 0; i < 8; i++) {
        std::cin >> target[i];
    }
    int start[8] = {1, 2, 3, 4, 5, 6, 7, 8}; // 基本状态
    int start_code = encode(start);
    int target_code = encode(target);

    // BFS：邻居固定按 A、B、C 顺序扩展，只在第一次到达时记录前驱。
    // 这样首次弹出目标时的路径既是最短的，也是同长度里字典序最小的。
    prev_state[start_code] = -1;
    bfs_queue.push(start_code);
    while (!bfs_queue.empty()) {
        int cur = bfs_queue.front();
        bfs_queue.pop();
        if (cur == target_code) {
            break;
        }
        int s[8];
        decode(cur, s);
        for (int op = 0; op < 3; op++) {
            int nxt[8];
            for (int i = 0; i < 8; i++) {
                nxt[i] = s[OPS[op][i]];
            }
            int nxt_code = encode(nxt);
            if (prev_state.find(nxt_code) == prev_state.end()) {
                prev_state[nxt_code] = cur;
                prev_op[nxt_code] = 'A' + op;
                bfs_queue.push(nxt_code);
            }
        }
    }

    // 从目标沿前驱回溯到基本状态，得到的是逆序的操作序列
    std::string answer;
    int cur = target_code;
    while (cur != start_code) {
        answer += prev_op[cur];
        cur = prev_state[cur];
    }
    ll len = answer.size();
    for (ll i = 0; i < len / 2; i++) {
        char tmp = answer[i];
        answer[i] = answer[len - 1 - i];
        answer[len - 1 - i] = tmp;
    }

    std::cout << len << "\n";
    // 除最后一行外每行输出 60 个字符
    for (ll i = 0; i < len; i += 60) {
        if (i > 0) {
            std::cout << "\n";
        }
        std::cout << answer.substr(i, 60);
    }
    return 0;
}
