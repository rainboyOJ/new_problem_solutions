/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:41
 * update_at: 2026-10-06 09:41
 */
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAX_SEQ = 200005;          // 输入 01 序列的最大长度
const int MAX_B = 12;                // 子串长度上限 B <= 12
const int VALUE_SPACE = 1 << MAX_B;  // 单个长度下模式串的数值上界 2^12

char seq[MAX_SEQ];                    // 输入的 01 序列
int cnt[MAX_B + 1][VALUE_SPACE];      // cnt[len][value]：定长 len 的模式串出现次数

struct Pattern {
    int freq;   // 该模式串的出现次数
    int len;    // 模式串长度
    int value;  // 模式串二进制对应的数值，定长时数值顺序即二进制字典序
};

Pattern pats[1 << (MAX_B + 1)];  // 不同模式串最多 sum(2^len) < 8192 个

// 排序规则：频次降序，其次长度升序，同长度按二进制字典序（数值）升序
bool cmp(const Pattern &a, const Pattern &b) {
    if (a.freq != b.freq) return a.freq > b.freq;
    if (a.len != b.len) return a.len < b.len;
    return a.value < b.value;
}

// 按定长输出模式串的二进制形式，高位不足补 0
void print_pattern(int value, int len) {
    char buf[MAX_B + 1];
    for (int i = 0; i < len; i++) {
        int bit = (value >> (len - 1 - i)) & 1;
        buf[i] = bit ? '1' : '0';
    }
    buf[len] = '\0';
    printf("%s", buf);
}

int main() {
    int A, B, N;
    if (scanf("%d %d %d", &A, &B, &N) != 3) return 0;

    // 读入序列：可能分成多行，直接拼接所有 0/1 字符
    int seq_len = 0;
    char token[1024];
    while (scanf("%1023s", token) == 1) {
        for (int i = 0; token[i] != '\0'; i++) {
            seq[seq_len] = token[i];
            seq_len++;
        }
    }

    // 对每个目标长度做滑动窗口，累计各模式串出现次数
    for (int len = A; len <= B; len++) {
        if (len > seq_len) break;
        int mask = (1 << len) - 1;
        int value = 0;
        for (int i = 0; i < len; i++) {
            value = (value << 1) | (seq[i] - '0');
        }
        cnt[len][value]++;
        for (int i = len; i < seq_len; i++) {
            value = ((value << 1) | (seq[i] - '0')) & mask;
            cnt[len][value]++;
        }
    }

    // 收集所有出现过的模式串
    int m = 0;
    for (int len = A; len <= B; len++) {
        if (len > seq_len) break;
        int total = 1 << len;
        for (int value = 0; value < total; value++) {
            if (cnt[len][value] > 0) {
                pats[m].freq = cnt[len][value];
                pats[m].len = len;
                pats[m].value = value;
                m++;
            }
        }
    }

    sort(pats, pats + m, cmp);

    // 按频次分组输出，最多输出前 N 种频次，每组内每行最多 6 个模式串
    int printed_freq = 0;
    int i = 0;
    while (i < m && printed_freq < N) {
        int freq = pats[i].freq;
        printf("%d\n", freq);
        int idx = 0;
        int j = i;
        while (j < m && pats[j].freq == freq) {
            if (idx > 0) {
                if (idx % 6 == 0) printf("\n");
                else printf(" ");
            }
            print_pattern(pats[j].value, pats[j].len);
            idx++;
            j++;
        }
        printf("\n");
        printed_freq++;
        i = j;
    }

    return 0;
}
