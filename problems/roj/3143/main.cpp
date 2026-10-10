/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 陪审团：按差值做 01 背包，层内按插入顺序扫描，位掩码记录成员集合。
#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <cstdlib>

typedef long long ll;

const int MW = 4; // n ≤ 200，成员掩码需要 4 个 64 位字

struct Mask {
    unsigned long long w[MW];
};

struct Entry {
    ll diff;  // D - P
    ll value; // P + D 之和
    Mask mask;
};

// 一层：entries 保持「插入顺序」（与 Python dict 的迭代顺序一致），idx 提供按键查找
struct Layer {
    std::vector<Entry> entries;
    std::map<ll, int> idx;
};

std::vector<ll> nums;
size_t npos = 0;

// 读入全部整数：先按行去掉 `//` 注释，再逐行分词
void read_all() {
    std::vector<char> raw;
    int ch;
    while ((ch = getchar()) != EOF) raw.push_back((char)ch);

    std::string text(raw.begin(), raw.end());
    size_t start = 0;
    while (start <= text.size()) {
        size_t nl = text.find('\n', start);
        std::string line = (nl == std::string::npos) ? text.substr(start) : text.substr(start, nl - start);
        size_t cm = line.find("//");
        if (cm != std::string::npos) line = line.substr(0, cm);
        const char* p = line.c_str();
        while (*p) {
            char* end;
            long long v = strtoll(p, &end, 10);
            if (end == p) break;
            nums.push_back(v);
            p = end;
        }
        if (nl == std::string::npos) break;
        start = nl + 1;
    }
    npos = 0;
}

int main() {
    read_all();
    std::vector<std::string> blocks;
    ll case_id = 0;

    while (npos + 2 <= nums.size()) {
        ll n = nums[npos++];
        ll m = nums[npos++];
        if (n == 0 && m == 0) break;
        case_id++;

        std::vector<ll> p(n), d(n);
        for (ll i = 0; i < n; i++) {
            p[i] = nums[npos++];
            d[i] = nums[npos++];
        }

        // 并列最优时打印哪一组由扫描顺序决定，按 |d-p| 降序先处理分歧大的候选人
        std::vector<ll> order(n);
        for (ll i = 0; i < n; i++) order[i] = i;
        for (ll i = 0; i < n; i++) { // 按 |d-p| 降序做稳定排序
            for (ll j = i + 1; j < n; j++) {
                ll a = d[order[i]] - p[order[i]];
                ll b = d[order[j]] - p[order[j]];
                if (a < 0) a = -a;
                if (b < 0) b = -b;
                if (b > a) {
                    ll t = order[i]; order[i] = order[j]; order[j] = t;
                }
            }
        }

        std::vector<Layer> layers(m + 1);
        for (ll t = 0; t < n; t++) {
            ll i = order[t];
            ll delta = d[i] - p[i];
            ll total = d[i] + p[i];
            Mask bit;
            for (int w = 0; w < MW; w++) bit.w[w] = 0;
            bit.w[i >> 6] |= 1ULL << (i & 63);

            // j 从大到小：本层只读上一层，保证同一个人不会被选两次
            for (ll j = m; j >= 2; j--) {
                Layer& layer = layers[j];
                Layer& prev = layers[j - 1];
                for (size_t q = 0; q < prev.entries.size(); q++) {
                    ll nd = prev.entries[q].diff + delta;
                    ll nv = prev.entries[q].value + total;
                    std::map<ll, int>::iterator it = layer.idx.find(nd);
                    if (it == layer.idx.end()) {
                        Entry e;
                        e.diff = nd;
                        e.value = nv;
                        e.mask = prev.entries[q].mask;
                        for (int w = 0; w < MW; w++) e.mask.w[w] |= bit.w[w];
                        layer.idx[nd] = (int)layer.entries.size();
                        layer.entries.push_back(e);
                    } else if (nv > layer.entries[it->second].value) {
                        layer.entries[it->second].value = nv;
                        layer.entries[it->second].mask = prev.entries[q].mask;
                        for (int w = 0; w < MW; w++) {
                            layer.entries[it->second].mask.w[w] |= bit.w[w];
                        }
                    }
                }
            }
            // 单人状态最后写：否则它会被上面的循环再叠一个人，变成两人一组
            {
                Layer& layer = layers[1];
                std::map<ll, int>::iterator it = layer.idx.find(delta);
                if (it == layer.idx.end()) {
                    Entry e;
                    e.diff = delta;
                    e.value = total;
                    e.mask = bit;
                    layer.idx[delta] = (int)layer.entries.size();
                    layer.entries.push_back(e);
                } else if (total > layer.entries[it->second].value) {
                    layer.entries[it->second].value = total;
                    layer.entries[it->second].mask = bit;
                }
            }
        }

        // 目标：|D-P| 最小，并列时 P+D 最大；min 取第一个最小元（插入顺序）
        Layer& last = layers[m];
        ll bestpos = 0;
        for (size_t q = 0; q < last.entries.size(); q++) {
            ll t = last.entries[q].diff;
            if (t < 0) t = -t;
            ll bt = last.entries[bestpos].diff;
            if (bt < 0) bt = -bt;
            if (t < bt || (t == bt && last.entries[q].value > last.entries[bestpos].value)) {
                bestpos = q;
            }
        }

        Mask chosen = last.entries[bestpos].mask;
        ll total = last.entries[bestpos].value;
        ll prosecution = 0;
        std::vector<ll> pick;
        for (ll i = 0; i < n; i++) {
            if ((chosen.w[i >> 6] >> (i & 63)) & 1ULL) {
                pick.push_back(i + 1);
                prosecution += p[i];
            }
        }

        char buf[256];
        std::string blk;
        snprintf(buf, sizeof(buf), "Jury #%lld\n", case_id);
        blk += buf;
        snprintf(buf, sizeof(buf),
                 "Best jury has value %lld for prosecution and value %lld for defence:\n",
                 prosecution, total - prosecution);
        blk += buf;
        for (size_t i = 0; i < pick.size(); i++) {
            snprintf(buf, sizeof(buf), " %lld", pick[i]);
            blk += buf;
        }
        blocks.push_back(blk);
    }

    for (size_t i = 0; i < blocks.size(); i++) {
        if (i) printf("\n\n");
        printf("%s", blocks[i].c_str());
    }
    printf("\n");
    return 0;
}
