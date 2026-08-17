/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
#include <bits/stdc++.h>
using namespace std;

// 一个补丁块：参考行号 start，原片段 old_part 与替换片段 new_part
struct Block {
    long long start;
    long long old_count;
    long long new_count;
    vector<string> old_part; // 原片段（- 行和上下文行）
    vector<string> new_part; // 新片段（+ 行和上下文行）
};

// 从 text 的 position 处读一个无前导零的正整数，成功则返回 true
bool read_positive_number(const string &text, int &position, long long &value) {
    if (position >= (int)text.size() || text[position] < '1' || text[position] > '9') return false;
    value = 0;
    while (position < (int)text.size() && '0' <= text[position] && text[position] <= '9') {
        int digit = text[position] - '0';
        if (value > (LLONG_MAX - digit) / 10) return false; // 溢出检查
        value = value * 10 + digit;
        position++;
    }
    return true;
}

// 解析块头 "@@ -start,old_count +new_start,new_count @@"，格式非法返回 false
bool read_header(const string &line, Block &block) {
    int position = 0;
    if (line.size() < 12 || line[0] != '@' || line[1] != '@' || line[2] != ' ' || line[3] != '-') {
        return false;
    }
    position = 4;
    if (!read_positive_number(line, position, block.start)) return false;
    if (position >= (int)line.size() || line[position] != ',') return false;
    position++;
    if (!read_positive_number(line, position, block.old_count)) return false;
    if (position >= (int)line.size() || line[position] != ' ') return false;
    position++;
    if (position >= (int)line.size() || line[position] != '+') return false;
    position++;
    long long ignored_new_start;
    if (!read_positive_number(line, position, ignored_new_start)) return false;
    if (position >= (int)line.size() || line[position] != ',') return false;
    position++;
    if (!read_positive_number(line, position, block.new_count)) return false;
    if (position + 3 != (int)line.size()) return false;
    if (line[position] != ' ' || line[position + 1] != '@' || line[position + 2] != '@') {
        return false;
    }
    return true;
}

// 判断文件中从 start 行开始的若干行是否等于 part 片段
bool same_lines(const vector<string> &file, long long start, const vector<string> &part) {
    for (int i = 0; i < (int)part.size(); i++) {
        if (file[(int)start - 1 + i] != part[i]) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    string line;
    getline(cin, line);
    vector<string> file(n);
    for (int i = 0; i < n; i++) getline(cin, file[i]);

    // 读取补丁：以 # 开头的行是注释，以 @ 开头的行开始一个新的块
    vector<vector<string> > raw_blocks;
    while (getline(cin, line)) {
        if (!line.empty() && line[0] == '#') continue;
        if (!line.empty() && line[0] == '@') {
            raw_blocks.push_back(vector<string>());
            raw_blocks.back().push_back(line);
        } else if (!raw_blocks.empty()) {
            raw_blocks.back().push_back(line);
        }
    }

    // 解析并校验每个块：头格式、行内容前缀、片段行数、相邻块不重叠
    bool damaged = raw_blocks.empty();
    vector<Block> blocks;
    if (!damaged) {
        for (int i = 0; i < (int)raw_blocks.size(); i++) {
            Block block;
            if (!read_header(raw_blocks[i][0], block)) {
                damaged = true;
                break;
            }
            for (int j = 1; j < (int)raw_blocks[i].size(); j++) {
                const string &content = raw_blocks[i][j];
                if (content.empty() ||
                    (content[0] != '-' && content[0] != '+' && content[0] != ' ')) {
                    damaged = true;
                    break;
                }
                if (content[0] != '+') block.old_part.push_back(content.substr(1));
                if (content[0] != '-') block.new_part.push_back(content.substr(1));
            }
            if (damaged) break;
            if (block.old_count != (long long)block.old_part.size() ||
                block.new_count != (long long)block.new_part.size()) {
                damaged = true;
                break;
            }
            if (!blocks.empty()) {
                if (blocks.back().start > LLONG_MAX - blocks.back().old_count ||
                    block.start < blocks.back().start + blocks.back().old_count) {
                    damaged = true;
                    break;
                }
            }
            blocks.push_back(block);
        }
    }

    // 依次应用每个块：在参考行号附近按规则寻找匹配位置并替换
    long long offset = 0;       // 此前所有块造成的累计行号偏移
    long long previous_end = 0; // 上一个块实际替换区间的结束行
    for (int i = 0; i < (int)blocks.size() && !damaged; i++) {
        Block &block = blocks[i];
        if (block.start > LLONG_MAX - offset) {
            damaged = true;
            break;
        }
        long long requested_start = block.start + offset;
        long long radius = block.old_count - 1;

        // 枚举偏移 delta，寻找匹配原片段的最优位置
        bool found = false;
        long long best_delta = 0;
        long long best_start = 0;
        for (long long delta = -radius; delta <= radius; delta++) {
            if ((delta > 0 && requested_start > LLONG_MAX - delta) ||
                (delta < 0 && requested_start < LLONG_MIN - delta)) {
                continue;
            }
            long long candidate = requested_start + delta;
            if (candidate < 1 || candidate > (long long)file.size() - (long long)block.old_part.size() + 1) {
                continue;
            }
            if (i > 0 && candidate < previous_end) continue; // 不能与上一个替换区间重叠
            if (!same_lines(file, candidate, block.old_part)) continue;
            // 选 |delta| 最小者，相同时选 delta 较小者
            if (!found || llabs(delta) < llabs(best_delta) ||
                (llabs(delta) == llabs(best_delta) && delta < best_delta)) {
                found = true;
                best_delta = delta;
                best_start = candidate;
            }
        }
        if (!found) {
            damaged = true;
            break;
        }

        // 用新片段替换原片段
        int erase_begin = (int)best_start - 1;
        file.erase(file.begin() + erase_begin,
                   file.begin() + erase_begin + (int)block.old_part.size());
        file.insert(file.begin() + erase_begin, block.new_part.begin(), block.new_part.end());
        if (offset > LLONG_MAX - best_delta) {
            damaged = true;
            break;
        }
        offset += best_delta;
        previous_end = best_start + (long long)block.old_part.size();
    }

    if (damaged) {
        cout << "Patch is damaged.\n";
        return 0;
    }
    for (int i = 0; i < (int)file.size(); i++) cout << file[i] << '\n';
    return 0;
}