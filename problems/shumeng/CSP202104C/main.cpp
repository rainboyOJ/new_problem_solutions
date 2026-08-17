/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;

// 地址的四种状态
enum Status { FREE, PENDING, OCCUPIED, EXPIRED };

// 一个 IP 地址的记录：状态、过期时刻、占用者
struct Address {
    int status;
    long long expire;
    string owner;
};

// 租约过期事件，堆顶为过期时刻最小的事件
struct ExpireEvent {
    long long time;
    int ip;
    bool operator<(const ExpireEvent &other) const {
        return time > other.time;
    }
};

int address_count;
long long default_time, maximum_time, minimum_time;
string server_name;
Address address[MAXN];
set<int> free_address, expired_address;   // 最小未分配与最小过期地址集合
priority_queue<ExpireEvent> expire_queue; // 过期事件队列
map<string, int> owner_ip;                // 主机名 -> 它占用的 IP

// 把地址释放为未分配状态，并清理相关记录
void set_free(int ip) {
    expired_address.erase(ip);
    owner_ip.erase(address[ip].owner);
    address[ip].status = FREE;
    address[ip].expire = 0;
    address[ip].owner.clear();
    free_address.insert(ip);
}

// 处理时刻 now 之前所有到期的租约
void process_expire(long long now) {
    while (!expire_queue.empty() && expire_queue.top().time <= now) {
        ExpireEvent event = expire_queue.top();
        expire_queue.pop();
        if (address[event.ip].expire != event.time) continue;   // 已被覆盖的过期事件
        if (address[event.ip].status == PENDING) {
            set_free(event.ip);                                 // 待分配到期 -> 未分配
        } else if (address[event.ip].status == OCCUPIED) {
            address[event.ip].status = EXPIRED;                 // 占用到期 -> 过期
            address[event.ip].expire = 0;
            expired_address.insert(event.ip);
        }
    }
}

// 根据请求过期时刻和上下限确定最终过期时刻
long long get_expire(long long now, long long requested) {
    if (requested == 0) return now + default_time;
    if (requested - now < minimum_time) return now + minimum_time;
    if (requested - now > maximum_time) return now + maximum_time;
    return requested;
}

// 把地址设为待分配，登记占用者并安排过期事件
void occupy_pending(int ip, const string &owner, long long expire) {
    free_address.erase(ip);
    expired_address.erase(ip);
    if (address[ip].owner != owner) owner_ip.erase(address[ip].owner);
    address[ip].status = PENDING;
    address[ip].owner = owner;
    owner_ip[owner] = ip;
    address[ip].expire = expire;
    expire_queue.push({expire, ip});
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> address_count >> default_time >> maximum_time >> minimum_time >> server_name;
    for (int i = 1; i <= address_count; i++) free_address.insert(i);
    int message_count;
    cin >> message_count;
    while (message_count--) {
        long long now, requested_expire;
        string sender, receiver, type;
        int ip;
        cin >> now >> sender >> receiver >> type >> ip >> requested_expire;
        process_expire(now);

        // 按题意过滤报文：接收者与类型必须符合要求
        if (receiver != server_name && receiver != "*" && type != "REQ") continue;
        if (type != "DIS" && type != "REQ") continue;
        if ((receiver == "*" && type != "DIS") || (receiver == server_name && type == "DIS")) continue;

        if (type == "DIS") {
            // 选择顺序：原有地址 > 最小未分配 > 最小过期
            int selected = owner_ip.count(sender) ? owner_ip[sender] : 0;
            if (selected == 0 && !free_address.empty()) selected = *free_address.begin();
            if (selected == 0 && !expired_address.empty()) selected = *expired_address.begin();
            if (selected == 0) continue;   // 无可用地址，忽略报文
            long long expire = get_expire(now, requested_expire);
            occupy_pending(selected, sender, expire);
            cout << server_name << ' ' << sender << " OFR " << selected << ' ' << expire << '\n';
            continue;
        }

        // Request 发给其它服务器：撤销发送方所有待分配地址
        if (receiver != server_name) {
            int selected = owner_ip.count(sender) ? owner_ip[sender] : 0;
            if (selected && address[selected].status == PENDING) set_free(selected);
            continue;
        }
        // Request 发给本机：校验占用者并确认租约
        if (ip < 1 || ip > address_count || address[ip].owner != sender) {
            cout << server_name << ' ' << sender << " NAK " << ip << " 0\n";
            continue;
        }
        free_address.erase(ip);
        expired_address.erase(ip);
        long long expire = get_expire(now, requested_expire);
        address[ip].status = OCCUPIED;
        address[ip].expire = expire;
        expire_queue.push({expire, ip});
        cout << server_name << ' ' << sender << " ACK " << ip << ' ' << expire << '\n';
    }

    return 0;
}