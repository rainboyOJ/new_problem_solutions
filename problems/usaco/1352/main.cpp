/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 21:10
 * update_at: 2026-07-11 21:13
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXC = 100005;
const int MAXP = 200015;

int target_count, command_count;
int offset_pos;
string cmd;

bool is_target[MAXP];
bool hit_in_prefix[MAXP];  // 当前分割点左侧，原始指令已经打中的目标。
bool right_side[5][MAXP];  // 位移 -2..2 下，右侧后缀能打中的目标。
bool pending_add[5][MAXP]; // 被右侧后缀打中，但暂时还在左侧前缀中。
int right_count[5];
int first_hit_time[MAXC];

int move_delta(char ch) {
    if (ch == 'L') return -1;
    if (ch == 'R') return 1;
    return 0;
}

void add_right_target(int idx, int pos) {
    if (pending_add[idx][pos]) {
        pending_add[idx][pos] = false;
    }
    if (!right_side[idx][pos]) {
        right_side[idx][pos] = true;
        right_count[idx]++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> target_count >> command_count;
    offset_pos = command_count;

    for (int i = 1; i <= target_count; i++) {
        int x;
        cin >> x;
        is_target[x + offset_pos] = true;
    }
    cin >> cmd;

    for (int i = 0; i < command_count; i++) {
        first_hit_time[i] = -1;
    }

    int cur_pos = offset_pos;
    int original_hits = 0;

    // 先模拟原始指令，记录每个目标第一次被打中的时刻。
    for (int i = 0; i < command_count; i++) {
        if (cmd[i] == 'F') {
            if (is_target[cur_pos] && !hit_in_prefix[cur_pos]) {
                hit_in_prefix[cur_pos] = true;
                first_hit_time[i] = cur_pos;
                original_hits++;
            }
        }
        cur_pos += move_delta(cmd[i]);
    }

    int ans = original_hits;
    int prefix_hits = original_hits;

    // 从右往左移动修改位置。cur_pos 表示执行完 i 号指令后的原始位置。
    for (int i = command_count - 1; i >= 0; i--) {
        if (first_hit_time[i] != -1) {
            int pos = first_hit_time[i];
            hit_in_prefix[pos] = false;
            prefix_hits--;

            for (int idx = 0; idx < 5; idx++) {
                if (pending_add[idx][pos]) {
                    add_right_target(idx, pos);
                }
            }
        }

        // 回到执行 i 号指令之前的位置。
        cur_pos -= move_delta(cmd[i]);

        if (cmd[i] == 'L') {
            // L -> F：当前位置开火，后缀整体相对原来右移 1。
            int add_now = 0;
            if (is_target[cur_pos] && !hit_in_prefix[cur_pos] && !right_side[3][cur_pos]) {
                add_now = 1;
            }
            ans = max(ans, prefix_hits + add_now + right_count[3]);

            // L -> R：后缀整体相对原来右移 2。
            ans = max(ans, prefix_hits + right_count[4]);
        } else if (cmd[i] == 'R') {
            // R -> F：当前位置开火，后缀整体相对原来左移 1。
            int add_now = 0;
            if (is_target[cur_pos] && !hit_in_prefix[cur_pos] && !right_side[1][cur_pos]) {
                add_now = 1;
            }
            ans = max(ans, prefix_hits + add_now + right_count[1]);

            // R -> L：后缀整体相对原来左移 2。
            ans = max(ans, prefix_hits + right_count[0]);
        } else {
            // F -> L / F -> R：当前不再开火，只改变后缀位移。
            ans = max(ans, prefix_hits + right_count[1]);
            ans = max(ans, prefix_hits + right_count[3]);
        }

        // 原始 i 号指令加入右侧后缀，供更靠左的修改位置使用。
        if (cmd[i] == 'F') {
            for (int pos = cur_pos - 2; pos <= cur_pos + 2; pos++) {
                if (pos < 0 || pos >= MAXP) continue;
                if (!is_target[pos]) continue;

                int idx = pos - cur_pos + 2;
                if (hit_in_prefix[pos]) {
                    if (!right_side[idx][pos]) {
                        pending_add[idx][pos] = true;
                    }
                } else {
                    add_right_target(idx, pos);
                }
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
