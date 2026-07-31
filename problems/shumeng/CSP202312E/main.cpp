/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 22:30
 */
#include <bits/stdc++.h>
using namespace std;

const long long NEGATIVE = -(1LL << 60);

struct Edge {
    int to;
    int weight;
};

struct CandidateIndex {
    vector<long long> value;
    vector<vector<unsigned long long> > conflict;
};

int n, m, limit, color_count;
vector<int> color;
vector<vector<Edge> > graph, reverse_graph;

bool compare_candidate(const pair<int, long long> &left,
        const pair<int, long long> &right) {
    return left.second > right.second;
}

CandidateIndex build_index(const vector<vector<unordered_map<int, long long> > > &states,
        int node, int middle_color, int maximum_depth) {
    vector<pair<int, long long> > candidate;
    for (int depth = 0; depth <= maximum_depth; depth++) {
        for (unordered_map<int, long long>::const_iterator it = states[depth][node].begin();
                it != states[depth][node].end(); ++it) {
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
        for (int bit = 0; bit < color_count; bit++) {
            if (candidate[i].first & (1 << bit)) {
                result.conflict[bit][i >> 6] |= 1ULL << (i & 63);
            }
        }
    }
    return result;
}

long long find_best(const CandidateIndex &index, int forbidden) {
    int word_count = (index.value.size() + 63) / 64;
    for (int word = 0; word < word_count; word++) {
        unsigned long long unavailable = 0;
        for (int bit = 0; bit < color_count; bit++) {
            if (forbidden & (1 << bit)) unavailable |= index.conflict[bit][word];
        }
        unsigned long long available = ~unavailable;
        if (word == word_count - 1 && index.value.size() % 64 != 0) {
            available &= (1ULL << (index.value.size() % 64)) - 1;
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

    int depth_limit = min(4, limit - 1);
    vector<vector<unordered_map<int, long long> > > forward(
        depth_limit + 1, vector<unordered_map<int, long long> >(n));
    vector<vector<unordered_map<int, long long> > > backward(
        depth_limit + 1, vector<unordered_map<int, long long> >(n));
    forward[0][0][1 << color[0]] = 0;
    backward[0][n - 1][1 << color[n - 1]] = 0;

    for (int depth = 0; depth < depth_limit; depth++) {
        for (int node = 0; node < n; node++) {
            for (unordered_map<int, long long>::const_iterator it = forward[depth][node].begin();
                    it != forward[depth][node].end(); ++it) {
                for (int i = 0; i < (int)graph[node].size(); i++) {
                    Edge edge = graph[node][i];
                    int bit = 1 << color[edge.to];
                    if (it->first & bit) continue;
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
                int forbidden = it->first ^ middle_bit;
                long long right_value = find_best(index[right_limit], forbidden);
                if (right_value != NEGATIVE) answer = max(answer, it->second + right_value);
            }
        }
    }
    cout << answer << '\n';

    return 0;
}
