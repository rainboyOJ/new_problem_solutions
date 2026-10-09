#!/usr/bin/env python3
# 2026-10-10 05:00
import sys

def solve() -> None:
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    n = int(input_data[0])
    m = int(input_data[1])
    k = int(input_data[2])
    l = int(input_data[3])
    r = int(input_data[4])
    
    adj = [[] for _ in range(n + 1)]
    idx = 5
    for _ in range(n - 1):
        u = int(input_data[idx])
        v = int(input_data[idx + 1])
        idx += 2
        adj[u].append(v)
        adj[v].append(u)
        
    ts = [0] * (n + 1)
    for _ in range(m):
        u = int(input_data[idx])
        idx += 1
        ts[u] = 1
        
    queries = []
    for _ in range(k):
        queries.append(int(input_data[idx]))
        idx += 1
        
    q_dist = [-1] * (n + 1)
    queue = []
    for i in range(1, n + 1):
        if ts[i]:
            queue.append(i)
            q_dist[i] = 0
            
    head = 0
    while head < len(queue):
        u = queue[head]
        head += 1
        for v in adj[u]:
            if q_dist[v] == -1:
                q_dist[v] = q_dist[u] + 1
                queue.append(v)
                
    yts = [0] * (n + 1)
    for i in range(1, n + 1):
        if l <= q_dist[i] <= r:
            yts[i] = 1
            
    fa = [0] * (n + 1)
    order = []
    queue = [1]
    vis = [False] * (n + 1)
    vis[1] = True
    
    head = 0
    while head < len(queue):
        u = queue[head]
        head += 1
        order.append(u)
        for v in adj[u]:
            if not vis[v]:
                vis[v] = True
                fa[v] = u
                queue.append(v)
                
    cnt = [0] * (n + 1)
    ycnt = [0] * (n + 1)
    dis = [0] * (n + 1)
    dis2 = [0] * (n + 1)
    ydis = [0] * (n + 1)
    
    for i in range(n - 1, -1, -1):
        u = order[i]
        cnt[u] = ts[u]
        ycnt[u] = yts[u]
        for v in adj[u]:
            if v == fa[u]:
                continue
            cnt[u] += cnt[v]
            ycnt[u] += ycnt[v]
            dis[u] += dis[v] + cnt[v]
            dis2[u] += dis2[v] + 2 * dis[v] + cnt[v]
            ydis[u] += ydis[v] + ycnt[v]
            
    total_cnt = cnt[1]
    total_ycnt = ycnt[1]
    
    for i in range(n):
        u = order[i]
        for v in adj[u]:
            if v == fa[u]:
                continue
            rem_cnt = total_cnt - cnt[v]
            rem_dis = dis[u] - (dis[v] + cnt[v])
            rem_dis2 = dis2[u] - (dis2[v] + 2 * dis[v] + cnt[v])
            
            dis2[v] += rem_dis2 + 2 * rem_dis + rem_cnt
            dis[v] += rem_dis + rem_cnt
            
            rem_ycnt = total_ycnt - ycnt[v]
            rem_ydis = ydis[u] - (ydis[v] + ycnt[v])
            
            ydis[v] += rem_ydis + rem_ycnt
            
    ans = [0] * (n + 1)
    for i in range(1, n + 1):
        ans[i] = dis2[i] + ydis[i]
        
    out = []
    for q in queries:
        out.append(str(ans[q]))
        
    sys.stdout.write('\n'.join(out) + '\n')

if __name__ == '__main__':
    sys.setrecursionlimit(200000)
    solve()
