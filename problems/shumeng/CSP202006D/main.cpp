/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;
const int STATE = 4;    // 字符种数：1,2,4,6
const int MATRIX = 5;   // 状态向量多一维常数项，便于在矩阵里加入跨边界项

string pattern;
int pattern_length, limit_length;   // limit_length = 模式串长度 - 1
string replace_text[STATE] = {"2", "4", "16", "64"};
string alphabet = "1246";
int transition[STATE][STATE];       // 替换矩阵：字母 a 的一次替换产生的各子字母数
vector<int> fail;                   // 模式串的 KMP 失配数组

// 某一时刻下各字母展开串截断后的前缀与后缀（长度不超过 limit_length）
struct TextState {
    string prefix[STATE], suffix[STATE];
};

// 用于快速幂的 5 阶转移矩阵
struct Matrix {
    long long value[MATRIX][MATRIX];
};

// 字符到下标：'1','2','4','6' -> 0,1,2,3
int get_id(char ch) {
    if (ch == '1') return 0;
    if (ch == '2') return 1;
    if (ch == '4') return 2;
    return 3;
}

// 构建模式串的 KMP 失配数组
void build_kmp() {
    fail.assign(pattern_length, 0);
    for (int i = 1; i < pattern_length; i++) {
        int position = fail[i - 1];
        while (position > 0 && pattern[position] != pattern[i]) position = fail[position - 1];
        if (pattern[position] == pattern[i]) position++;
        fail[i] = position;
    }
}

// 统计 left + right 拼接串中跨越边界 boundary 的完整模式匹配个数
int count_cross(const string &left, const string &right) {
    string text = left + right;
    int answer = 0, matched = 0, boundary = (int)left.size();
    for (int i = 0; i < (int)text.size(); i++) {
        while (matched > 0 && pattern[matched] != text[i]) matched = fail[matched - 1];
        if (pattern[matched] == text[i]) matched++;
        if (matched == pattern_length) {
            int start = i - pattern_length + 1;
            if (start < boundary && start + pattern_length > boundary) answer++;
            matched = fail[matched - 1];
        }
    }
    return answer;
}

// 由当前时刻的各字母前后缀，推出下一时刻的前后缀
TextState next_state(const TextState &current) {
    TextState next;
    for (int a = 0; a < STATE; a++) {
        for (int i = 0; i < (int)replace_text[a].size(); i++) {
            int child = get_id(replace_text[a][i]);
            if ((int)next.prefix[a].size() < limit_length) {
                next.prefix[a] += current.prefix[child];
                if ((int)next.prefix[a].size() > limit_length) next.prefix[a].resize(limit_length);
            }
            next.suffix[a] += current.suffix[child];
            if ((int)next.suffix[a].size() > limit_length) {
                next.suffix[a] = next.suffix[a].substr(next.suffix[a].size() - limit_length);
            }
        }
    }
    return next;
}

// 两个时刻的前后缀状态是否完全相同（用于判断六周期）
bool same_state(const TextState &left, const TextState &right) {
    for (int i = 0; i < STATE; i++) {
        if (left.prefix[i] != right.prefix[i] || left.suffix[i] != right.suffix[i]) return false;
    }
    return true;
}

// 走一轮替换：每种字母的出现次数由上一轮线性转移加上跨边界匹配数
array<long long, STATE> step(const array<long long, STATE> &old, const array<long long, STATE> &cross) {
    array<long long, STATE> next = {};
    for (int a = 0; a < STATE; a++) {
        next[a] = cross[a];
        for (int b = 0; b < STATE; b++) next[a] = (next[a] + 1LL * transition[a][b] * old[b]) % MOD;
    }
    return next;
}

// 矩阵乘法
Matrix multiply(const Matrix &left, const Matrix &right) {
    Matrix result = {};
    for (int i = 0; i < MATRIX; i++) {
        for (int k = 0; k < MATRIX; k++) {
            if (left.value[i][k] == 0) continue;
            for (int j = 0; j < MATRIX; j++) {
                result.value[i][j] = (result.value[i][j] + left.value[i][k] * right.value[k][j]) % MOD;
            }
        }
    }
    return result;
}

// 矩阵快速幂
Matrix power(Matrix base, long long exponent) {
    Matrix result = {};
    for (int i = 0; i < MATRIX; i++) result.value[i][i] = 1;
    while (exponent) {
        if (exponent & 1) result = multiply(result, base);
        base = multiply(base, base);
        exponent >>= 1;
    }
    return result;
}

// 矩阵乘状态向量（最后一维固定为 1，表示常数维）
array<long long, MATRIX> apply_matrix(const Matrix &matrix, const array<long long, MATRIX> &vector_value) {
    array<long long, MATRIX> result = {};
    for (int i = 0; i < MATRIX; i++) {
        for (int j = 0; j < MATRIX; j++) result[i] = (result[i] + matrix.value[i][j] * vector_value[j]) % MOD;
    }
    return result;
}

// 由当前轮的跨边界项构造一轮转移矩阵（含常数维）
Matrix make_matrix(const array<long long, STATE> &cross) {
    Matrix result = {};
    for (int i = 0; i < STATE; i++) {
        for (int j = 0; j < STATE; j++) result.value[i][j] = transition[i][j];
        result.value[i][STATE] = cross[i];
    }
    result.value[STATE][STATE] = 1;
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n >> pattern;
    pattern_length = (int)pattern.size();
    // 预处理替换矩阵 transition[a][b]
    for (int a = 0; a < STATE; a++) {
        for (int i = 0; i < (int)replace_text[a].size(); i++) transition[a][get_id(replace_text[a][i])]++;
    }

    array<long long, STATE> initial = {};
    if (pattern_length == 1) {
        // 单字符模式：不存在跨边界项，直接对纯替换矩阵快速幂
        for (int i = 0; i < STATE; i++) initial[i] = pattern[0] == alphabet[i];
        array<long long, STATE> zero_cross = {};
        Matrix plain = make_matrix(zero_cross);
        array<long long, MATRIX> vector_value = {initial[0], initial[1], initial[2], initial[3], 1};
        cout << apply_matrix(power(plain, n), vector_value)[0] << '\n';
        return 0;
    }

    build_kmp();
    limit_length = pattern_length - 1;
    TextState current;
    for (int i = 0; i < STATE; i++) current.prefix[i] = current.suffix[i] = string(1, alphabet[i]);
    vector<array<long long, STATE> > cross_list;   // 每轮的跨边界项
    vector<array<long long, STATE> > count_list(1, initial);   // 每轮的 F 值，count_list[0] 为第 0 轮
    deque<TextState> recent;
    recent.push_back(current);

    // 逐轮推进，直到连续 6 轮的前后缀状态重复（六周期）
    int time = 0, begin = -1;
    while (true) {
        array<long long, STATE> cross = {};
        // 跨边界匹配只可能出现在 4 -> 16 和 6 -> 64 这两处替换
        cross[2] = count_cross(current.suffix[0], current.prefix[3]);
        cross[3] = count_cross(current.suffix[3], current.prefix[2]);
        cross_list.push_back(cross);
        count_list.push_back(step(count_list.back(), cross));
        current = next_state(current);
        time++;
        recent.push_back(current);
        if ((int)recent.size() == 7) {
            if (same_state(recent.front(), recent.back())) {
                begin = time - 6;
                break;
            }
            recent.pop_front();
        }
    }
    if (n <= time) {
        cout << count_list[n][0] << '\n';
        return 0;
    }

    // 把周期内 6 个矩阵连乘，再快速幂跳过大量轮数
    Matrix period = {};
    for (int i = 0; i < MATRIX; i++) period.value[i][i] = 1;
    for (int i = 0; i < 6; i++) period = multiply(make_matrix(cross_list[begin + i]), period);
    array<long long, MATRIX> vector_value = {count_list[begin][0], count_list[begin][1], count_list[begin][2], count_list[begin][3], 1};
    long long repeat = (n - begin) / 6;
    vector_value = apply_matrix(power(period, repeat), vector_value);
    // 剩余不足一个周期的轮数逐轮处理
    int remain = (int)((n - begin) % 6);
    for (int i = 0; i < remain; i++) vector_value = apply_matrix(make_matrix(cross_list[begin + i]), vector_value);
    cout << vector_value[0] << '\n';

    return 0;
}