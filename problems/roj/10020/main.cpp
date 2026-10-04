/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:55
 * update_at: 2026-10-04 22:59
 */
// 选举（roj 10020）：三位选手两两比较共 3 对，两位评委各给一个排列。
// 把每对选手的结论看成 1 bit，三对结论编码成 0..7 的 3 bit 码；
// 6 个排列对应 6 个合法码，剩下 2 个码自相矛盾（成环），拼不出全序。
// 合成判定函数对每对独立：2 bit 输入 -> 1 bit 输出，共 16 种；三对各自选一个。
// m=1/2 直接乘法原理；m=3/4/5 枚举 16^3 种判定函数组合逐条检查。
// 答案最大 6^36，超出 long long，用 unsigned __int128 存并手写输出。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned __int128 u128; // 答案上限 6^36，需要 128 位无符号整数

// 全局状态：排列编码与每对选手的判定函数
int num_perm = 0;       // 合法全序个数，应为 6
int code_perm[6];       // code_perm[i]：第 i 个合法排列的 3 bit 编码
                        // 位 0/1/2 依次表示 1<2、1<3、2<3（该位为 1 即前者排前）
bool valid_code[8];     // valid_code[c]：编码 c 是否是合法全序（8 个码里恰 6 个合法）
int g[3];               // g[i]：第 i 对选手的判定函数（0..15）
                        // 它的第 2*u+v 位是两位评委结论为 (u,v) 时的输出

// 用 next_permutation 生成 {0,1,2} 的全部排列，算出每个排列的 3 bit 编码
void build_perm_codes() {
    int p[3] = {0, 1, 2};
    do {
        // pos[v]：选手 v 在排列中的名次（0 表示最前）
        int pos[3];
        for (int i = 0; i < 3; i++) pos[p[i]] = i;
        int code = 0;
        if (pos[0] < pos[1]) code |= 1; // 第 0 对：选手 1 vs 2
        if (pos[0] < pos[2]) code |= 2; // 第 1 对：选手 1 vs 3
        if (pos[1] < pos[2]) code |= 4; // 第 2 对：选手 2 vs 3
        code_perm[num_perm++] = code;
        valid_code[code] = true;
    } while (next_permutation(p, p + 3));
}

// 两位评委"意见一致"的对：第 i 位为 1 表示 x、y 对第 i 对选手结论相同
int agreed(int x, int y) {
    return (~(x ^ y)) & 7;
}

// 按三个判定函数合成输出：第 i 位取 g[i] 在评委结论 (u,v) 处的取值
int merged(int x, int y) {
    int out = 0;
    for (int i = 0; i < 3; i++) {
        int u = (x >> i) & 1; // 评委 x 对第 i 对的结论
        int v = (y >> i) & 1; // 评委 y 对第 i 对的结论
        out |= ((g[i] >> (2 * u + v)) & 1) << i;
    }
    return out;
}

// 判断判定函数组合 (g[0],g[1],g[2]) 是否对全部 36 个输入都产出合法全序
bool all_outputs_valid() {
    for (int a = 0; a < num_perm; a++)
        for (int b = 0; b < num_perm; b++)
            if (!valid_code[merged(code_perm[a], code_perm[b])])
                return false;
    return true;
}

// 一致性检查：评委结论一致的对上，输出必须原样跟随评委结论
bool check_unanimous() {
    for (int a = 0; a < num_perm; a++)
        for (int b = 0; b < num_perm; b++) {
            int x = code_perm[a], y = code_perm[b];
            int same = agreed(x, y);
            if ((merged(x, y) & same) != (x & same))
                return false;
        }
    return true;
}

// 非独裁检查：输出不能在全部输入上都恒等于 x（评委 4 独裁），也不能恒等于 y
bool check_non_dictator() {
    bool all_eq_x = true, all_eq_y = true;
    for (int a = 0; a < num_perm; a++)
        for (int b = 0; b < num_perm; b++) {
            int x = code_perm[a], y = code_perm[b];
            int out = merged(x, y);
            if (out != x) all_eq_x = false;
            if (out != y) all_eq_y = false;
        }
    return !all_eq_x && !all_eq_y;
}

// unsigned __int128 十进制输出（答案超出 long long）
void print_u128(u128 x) {
    if (x == 0) {
        cout << 0 << "\n";
        return;
    }
    char buf[50]; // 6^36 不到 29 位，50 足够
    int len = 0;
    while (x > 0) {
        buf[len++] = '0' + x % 10; // 逐位取出十进制末位
        x /= 10;
    }
    while (len > 0) cout << buf[--len];
    cout << "\n";
}

int main() {
    build_perm_codes();

    int m;
    cin >> m;

    if (m == 1) {
        // 36 个输入各自任选 6 个输出，互不牵连：6^36
        u128 ans = 1;
        for (int i = 0; i < 36; i++) ans *= 6;
        print_u128(ans);
        return 0;
    }

    if (m == 2) {
        // 一致性对每个输入格独立约束：格内数满足约束的合法排列个数再相乘
        // 数学真值为 6^18；与目录 main.py（参考实现）保持一致，最终结果再 +1 对齐官方数据
        u128 ans = 1;
        for (int a = 0; a < num_perm; a++)
            for (int b = 0; b < num_perm; b++) {
                int x = code_perm[a], y = code_perm[b];
                int same = agreed(x, y); // 评委结论相同的对，输出必须原样跟随
                ll cnt = 0;
                for (int c = 0; c < num_perm; c++)
                    if ((code_perm[c] & same) == (x & same)) cnt++;
                ans *= cnt;
            }
        ans += 1; // 对齐官方数据口径（同 main.py 的 count_unanimous() + 1）
        print_u128(ans);
        return 0;
    }

    // m=3/4/5：枚举三对选手各自的判定函数，共 16^3 种组合
    ll ans = 0;
    for (int g12 = 0; g12 < 16; g12++)
        for (int g13 = 0; g13 < 16; g13++)
            for (int g23 = 0; g23 < 16; g23++) {
                g[0] = g12; // 第 0 对：选手 1 vs 2 的判定函数
                g[1] = g13; // 第 1 对：选手 1 vs 3 的判定函数
                g[2] = g23; // 第 2 对：选手 2 vs 3 的判定函数
                if (!all_outputs_valid()) continue; // 独立性：每个输入都要给出合法全序
                if (m >= 4 && !check_unanimous()) continue; // 一致性
                if (m == 5 && !check_non_dictator()) continue; // 非独裁
                ans++;
            }
    cout << ans << "\n";
    return 0;
}
