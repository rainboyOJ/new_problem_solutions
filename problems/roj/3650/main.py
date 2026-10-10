import sys
import heapq

sys.setrecursionlimit(2000000)

def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return
        
    t = int(data[0])
    idx = 1
    
    out = []
    
    for _ in range(t):
        n = int(data[idx])
        m = int(data[idx+1])
        k = int(data[idx+2])
        p = int(data[idx+3])
        idx += 4
        
        adj = [[] for _ in range(n + 1)]
        rev_adj = [[] for _ in range(n + 1)]
        
        for _ in range(m):
            u = int(data[idx])
            v = int(data[idx+1])
            w = int(data[idx+2])
            idx += 3
            adj[u].append((v, w))
            rev_adj[v].append((u, w))
            
        def dijkstra(start, graph):
            dist = [float('inf')] * (n + 1)
            dist[start] = 0
            pq = [(0, start)]
            
            while pq:
                d, u = heapq.heappop(pq)
                if d > dist[u]:
                    continue
                for v, w in graph[u]:
                    if dist[u] + w < dist[v]:
                        dist[v] = dist[u] + w
                        heapq.heappush(pq, (dist[v], v))
            return dist
            
        dist = dijkstra(1, adj)
        rev_dist = dijkstra(n, rev_adj)
        
        dp = [[-1] * (k + 1) for _ in range(n + 1)]
        in_stack = [[False] * (k + 1) for _ in range(n + 1)]
        has_infinity = False
        
        def dfs(u, j):
            nonlocal has_infinity
            
            if dist[u] + j + rev_dist[u] > dist[n] + k:
                return 0
                
            if in_stack[u][j]:
                has_infinity = True
                return 0
                
            if dp[u][j] != -1:
                return dp[u][j]
                
            in_stack[u][j] = True
            ways = 0
            
            if u == n:
                ways = 1
                
            for v, w in adj[u]:
                next_j = j + dist[u] + w - dist[v]
                if next_j <= k:
                    ways = (ways + dfs(v, next_j)) % p
                    if has_infinity:
                        in_stack[u][j] = False
                        return 0
                        
            in_stack[u][j] = False
            dp[u][j] = ways
            return ways
            
        ans = dfs(1, 0)
        
        if has_infinity:
            out.append("-1")
        else:
            out.append(str(ans))
            
    print('\n'.join(out))

if __name__ == '__main__':
    solve()
