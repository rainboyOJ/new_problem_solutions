/**
 * Author by Rainboy
 */
// brute.cpp：O(1) get / O(n) put（线性扫描）。
#include <bits/stdc++.h>
using namespace std;

class LRUCache {
    vector<pair<int,int>> data;
    int cap;
public:
    LRUCache(int capacity) : cap(capacity) {}
    int get(int key) {
        for (size_t i = 0; i < data.size(); i++) {
            if (data[i].first == key) {
                auto tmp = data[i];
                data.erase(data.begin() + i);
                data.push_back(tmp);
                return tmp.second;
            }
        }
        return -1;
    }
    void put(int key, int value) {
        for (size_t i = 0; i < data.size(); i++) {
            if (data[i].first == key) {
                data.erase(data.begin() + i);
                data.push_back({key, value});
                return;
            }
        }
        if ((int)data.size() == cap) data.erase(data.begin());
        data.push_back({key, value});
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int cap, ops; cin >> cap >> ops;
    LRUCache cache(cap);
    while (ops--) {
        string op; cin >> op;
        if (op == "get") { int k; cin >> k; cout << cache.get(k) << ' '; }
        else { int k, v; cin >> k >> v; cache.put(k, v); }
    }
    return 0;
}
