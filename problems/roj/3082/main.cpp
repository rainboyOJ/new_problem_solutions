/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 17:39
 * update_at: 2026-10-06 17:39
 */
#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <vector>
#include <climits>

typedef long long ll;

const int SIDE_STEPS = 5; // 双向 BFS 每侧最多扩展的层数，两侧合计覆盖题面的 10 步上限

std::vector<std::pair<std::string, std::string> > rules;      // 正向规则 left -> right
std::vector<std::pair<std::string, std::string> > back_rules; // 反向规则 right -> left，B 侧沿逆规则扩展

std::map<std::string, int> dist_a; // A 侧已发现的串 -> 到 A 的最少步数
std::map<std::string, int> dist_b; // B 侧已发现的串 -> 到 B 的最少步数
std::queue<std::string> qa;        // A 侧待扩展队列
std::queue<std::string> qb;        // B 侧待扩展队列

// 把 q 中当前一层的所有串向 rs 中的规则扩展一层，距离写进 dist。
void extend_layer(std::queue<std::string> &q, std::map<std::string, int> &dist,
                  std::vector<std::pair<std::string, std::string> > &rs) {
    int layer_size = q.size();
    for (int idx = 0; idx < layer_size; idx++) {
        std::string s = q.front();
        q.pop();
        int d = dist[s];
        if (d == SIDE_STEPS) {
            continue; // 该侧已到层数上限，不再向外扩展
        }
        for (int r = 0; r < (int)rs.size(); r++) {
            std::string left = rs[r].first;
            std::string right = rs[r].second;
            // 找 left 在 s 中的每次出现；找到一次后从下一位继续，覆盖重叠出现
            size_t pos = s.find(left, 0);
            while (pos != std::string::npos) {
                std::string nxt = s.substr(0, pos) + right + s.substr(pos + left.size());
                if (dist.find(nxt) == dist.end()) {
                    dist[nxt] = d + 1;
                    q.push(nxt);
                }
                pos = s.find(left, pos + 1);
            }
        }
    }
}

int main() {
    std::string start;
    std::string target;
    if (!(std::cin >> start >> target)) {
        return 0;
    }
    if (start == target) {
        std::cout << 0 << std::endl;
        return 0;
    }
    std::string left;
    std::string right;
    while (std::cin >> left >> right) {
        rules.push_back(std::make_pair(left, right));
        back_rules.push_back(std::make_pair(right, left));
    }

    dist_a[start] = 0;
    qa.push(start);
    dist_b[target] = 0;
    qb.push(target);

    for (int k = 1; k <= SIDE_STEPS; k++) {
        extend_layer(qa, dist_a, rules);
        extend_layer(qb, dist_b, back_rules);

        // 交点 s 给出一条 A -> s -> B 的合法路径，两侧距离之和是一条真实路径长度；
        // 当和 <= 2k 时，最短路的中间点两侧都已在 k 层内发现，该和恰为答案
        int best = INT_MAX;
        std::map<std::string, int>::iterator it;
        for (it = dist_a.begin(); it != dist_a.end(); ++it) {
            std::map<std::string, int>::iterator jt = dist_b.find(it->first);
            if (jt != dist_b.end()) {
                int sum = it->second + jt->second;
                if (sum < best) {
                    best = sum;
                }
            }
        }
        if (best <= 2 * k) {
            std::cout << best << std::endl;
            return 0;
        }
    }

    std::cout << "NO ANSWER!" << std::endl;
    return 0;
}
