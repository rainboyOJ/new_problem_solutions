/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:40
 */
#include <bits/stdc++.h>
using namespace std;

const long long NEGATIVE = -(1LL << 60); // 表示不可达的极小值

struct Edge {
    int to;     // 边的终点
    int weight; // 边的长度
};

// 后半段候选状态的索引：按权值降序排列，并用位集记录每个颜色出现在哪些候选里
struct CandidateIndex {
    vector<long long> value;                    // 候选按权值降序排列的长度
    vector<vector<unsigned long long> > conflict; // conflict[c][w] 表示颜色 c 在候选区间 w 内占用了哪些位
};

int n, m, limit, color_count;
vector<int> color;                        // 每个节点的颜色标签
vector<vector<Edge> > graph, reverse_graph; // 原图与反向图

// 候选状态按长度降序排序
bool compare_candidate(const pair<int, long long> &left,
        const pair<int, long long> &right) {
    return left.second > right.second;
}

// 对某个中间节点 node 建立后半段候选索引。
// states 是某方向的状态表，middle_color 是要去掉的中间节点颜色（两段都包含它）。
CandidateIndex build_index(const vector<vector<unordered_map<int, long long> > > &states,
        int node, int middle_color, int maximum_depth) {
    vector<pair<int, long long> > candidate;
    for (int depth = 0; depth <= maximum_depth; depth++) {
        for (unordered_map<int, long long>::const_iterator it = states[depth][node].begin();
                it != states[depth][node].end(); ++it) {
            // 去掉中间节点的颜色位，避免前后两段重复计算
            candidate.push_back({it->first ^ (1 << middle_color), it->second});
        }
    }
    sort(candidate.begin(), candidate.end(), compare_candidate);

    CandidateIndex result;
    int word_count = ((int)candidate.size() + 63) / 64;
    result.value.resize(candidate.size());
    result.conflict.assign(color_count, vector<unsigned long long>(word_count, 0));
    for (int i = 0; i < (int)candidate.size(); i++) {
        result.value[i] = candidate[i].second;
        // 候选 i 含有的每个颜色，都在对应位集里标记这一位
        for (int bit = 0; bit < color_count; bit++) {
            if (candidate[i].first & (1 << bit)) {
                result.conflict[bit][i >> 6] |= 1ULL << (i & 63);
            }
        }
    }
    return result;
}

// 在候选索引中找与 forbidden 颜色集合不相交的、长度最大的候选。
// 利用位集把 forbidden 包含的颜色对应的位取并集，剩余未占用的最低位即最优候选。
long long find_best(const CandidateIndex &index, int forbidden) {
    int word_count = (index.value.size() + 63) / 64;
    for (int word = 0; word < word_count; word++) {
        unsigned long long unavailable = 0;
        for (int bit = 0; bit < color_count; bit++) {
            if (forbidden & (1 << bit)) unavailable |= index.conflict[bit][word];
        }
        unsigned long long available = ~unavailable;
        if (word == word_count - 1 && index.value.size() % 64 != 0) {
            available &= (1ULL << (index.value.size() % 64)) - 1; // 去掉最后一组多余位
        }
        if (available != 0) {
            int position = word * 64 + __builtin_ctzll(available);
            return index.value[position];
        }
    }
    return NEGATIVE;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> limit >> color_count;
    color.resize(n);
    for (int i = 0; i < n; i++) cin >> color[i];
    graph.resize(n);
    reverse_graph.resize(n);
    vector<int> from(m), to(m), length(m);
    for (int i = 0; i < m; i++) cin >> from[i];
    for (int i = 0; i < m; i++) cin >> to[i];
    for (int i = 0; i < m; i++) cin >> length[i];
    for (int i = 0; i < m; i++) {
        graph[from[i]].push_back({to[i], length[i]});
        reverse_graph[to[i]].push_back({from[i], length[i]});
    }

    // 路径最多 limit-1 条边，折半后每段最多 4 条边
    int depth_limit = min(4, limit - 1);
    // forward[d][v][mask]：从 0 出发走 d 条边到 v，颜色集合为 mask 的最大长度
    // backward[d][v][mask]：从 v 出发走 d 条边到 n-1，颜色集合为 mask 的最大长度
    vector<vector<unordered_map<int, long long> > > forward(
        depth_limit + 1, vector<unordered_map<int, long long> >(n));
    vector<vector<unordered_map<int, long long> > > backward(
        depth_limit + 1, vector<unordered_map<int, long long> >(n));
    forward[0][0][1 << color[0]] = 0;
    backward[0][n - 1][1 << color[n - 1]] = 0;

    // 向两边同时做状压 DP：每次沿一条边转移，拒绝已出现的颜色
    for (int depth = 0; depth < depth_limit; depth++) {
        for (int node = 0; node < n; node++) {
            for (unordered_map<int, long long>::const_iterator it = forward[depth][node].begin();
                    it != forward[depth][node].end(); ++it) {
                for (int i = 0; i < (int)graph[node].size(); i++) {
                    Edge edge = graph[node][i];
                    int bit = 1 << color[edge.to];
                    if (it->first & bit) continue; // 目标颜色已出现过
                    int mask = it->first | bit;
                    long long value = it->second + edge.weight;
                    long long &best = forward[depth + 1][edge.to][mask];
                    if (best < value) best = value;
                }
            }
            for (unordered_map<int, long long>::const_iterator it = backward[depth][node].begin();
                    it != backward[depth][node].end(); ++it) {
                for (int i = 0; i < (int)reverse_graph[node].size(); i++) {
                    Edge edge = reverse_graph[node][i];
                    int bit = 1 << color[edge.to];
                    if (it->first & bit) continue;
                    int mask = it->first | bit;
                    long long value = it->second + edge.weight;
                    long long &best = backward[depth + 1][edge.to][mask];
                    if (best < value) best = value;
                }
            }
        }
    }

    // 枚举中间节点，合并前后两段：两段颜色集合必须不相交
    long long answer = 0;
    for (int node = 0; node < n; node++) {
        int middle_bit = 1 << color[node];
        vector<CandidateIndex> index(depth_limit + 1);
        for (int depth = 0; depth <= depth_limit; depth++) {
            index[depth] = build_index(backward, node, color[node], depth);
        }
        for (int left_depth = 0; left_depth <= depth_limit; left_depth++) {
            for (unordered_map<int, long long>::const_iterator it = forward[left_depth][node].begin();
                    it != forward[left_depth][node].end(); ++it) {
                int right_limit = min(depth_limit, limit - 1 - left_depth);
                if (right_limit < 0) continue;
                // 后半段颜色不能包含前半段已用的颜色（去掉中间的公共颜色）
                int forbidden = it->first ^ middle_bit;
                long long right_value = find_best(index[right_limit], forbidden);
                if (right_value != NEGATIVE) answer = max(answer, it->second + right_value);
            }
        }
    }
    cout << answer << '\n';

    return 0;
}