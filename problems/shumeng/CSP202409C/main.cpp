/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 01:21
 */
#include <bits/stdc++.h>
using namespace std;

struct Block {
    long long start;
    long long old_count;
    long long new_count;
    vector<string> old_part;
    vector<string> new_part;
};

bool read_positive_number(const string &text, int &position, long long &value) {
    if (position >= (int)text.size() || text[position] < '1' || text[position] > '9') return false;
    value = 0;
    while (position < (int)text.size() && '0' <= text[position] && text[position] <= '9') {
        int digit = text[position] - '0';
        if (value > (LLONG_MAX - digit) / 10) return false;
        value = value * 10 + digit;
        position++;
    }
    return true;
}

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

    long long offset = 0;
    long long previous_end = 0;
    for (int i = 0; i < (int)blocks.size() && !damaged; i++) {
        Block &block = blocks[i];
        if (block.start > LLONG_MAX - offset) {
            damaged = true;
            break;
        }
        long long requested_start = block.start + offset;
        long long radius = block.old_count - 1;
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
            if (i > 0 && candidate < previous_end) continue;
            if (!same_lines(file, candidate, block.old_part)) continue;
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
