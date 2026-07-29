/**
 * Author by Rainboy
 */
// main.cpp：unordered_map + list，O(1) get/put。
#include <bits/stdc++.h>
using namespace std;

class LRUCache {
    int cap;
    list<pair<int, int>> lst;
    unordered_map<int, decltype(lst)::iterator> mp;

public:
    LRUCache(int capacity) : cap(capacity) {}

    int get(int key) {
        auto it = mp.find(key);
        if (it == mp.end())
            return -1;
        lst.splice(lst.begin(), lst, it->second);
        return it->second->second;
    }

    void put(int key, int value) {
        auto it = mp.find(key);
        if (it != mp.end()) {
            it->second->second = value;
            lst.splice(lst.begin(), lst, it->second);
            return;
        }
        if ((int)lst.size() == cap) {
            mp.erase(lst.back().first);
            lst.pop_back();
        }
        lst.push_front({key, value});
        mp[key] = lst.begin();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int cap, ops;
    cin >> cap >> ops;
    LRUCache cache(cap);
    while (ops--) {
        string op;
        cin >> op;
        if (op == "get") {
            int k;
            cin >> k;
            cout << cache.get(k) << ' ';
        } else {
            int k, v;
            cin >> k >> v;
            cache.put(k, v);
        }
    }
    return 0;
}
