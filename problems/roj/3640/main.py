import sys

def main():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return
    
    n, m, v, e = map(int, data[:4])
    idx = 4
    
    c = [0] + [int(x) for x in data[idx:idx+n]]
    idx += n
    d = [0] + [int(x) for x in data[idx:idx+n]]
    idx += n
    k = [0.0] + [float(x) for x in data[idx:idx+n]]
    idx += n
    
    dis = [[float('inf')] * (v + 1) for _ in range(v + 1)]
    for i in range(1, v + 1):
        dis[i][i] = 0
        
    for _ in range(e):
        u = int(data[idx])
        v_node = int(data[idx+1])
        w = int(data[idx+2])
        idx += 3
        if w < dis[u][v_node]:
            dis[u][v_node] = dis[v_node][u] = w
            
    for p in range(1, v + 1):
        for i in range(1, v + 1):
            if dis[i][p] != float('inf'):
                for j in range(1, v + 1):
                    if dis[i][p] + dis[p][j] < dis[i][j]:
                        dis[i][j] = dis[i][p] + dis[p][j]
                        
    f = [[float('inf')] * 2 for _ in range(m + 1)]
    f[0][0] = 0.0
    if m >= 1:
        f[1][1] = 0.0
        
    for i in range(2, n + 1):
        nf = [[float('inf')] * 2 for _ in range(m + 1)]
        c_prev, d_prev, k_prev = c[i-1], d[i-1], k[i-1]
        c_curr, d_curr, k_curr = c[i], d[i], k[i]
        
        for j in range(min(i, m) + 1):
            v1 = f[j][0] + dis[c_prev][c_curr]
            v2 = f[j][1] + k_prev * dis[d_prev][c_curr] + (1.0 - k_prev) * dis[c_prev][c_curr]
            nf[j][0] = min(v1, v2)
            
            if j > 0:
                v3 = f[j-1][0] + k_curr * dis[c_prev][d_curr] + (1.0 - k_curr) * dis[c_prev][c_curr]
                v4 = f[j-1][1] + \
                     k_prev * k_curr * dis[d_prev][d_curr] + \
                     k_prev * (1.0 - k_curr) * dis[d_prev][c_curr] + \
                     (1.0 - k_prev) * k_curr * dis[c_prev][d_curr] + \
                     (1.0 - k_prev) * (1.0 - k_curr) * dis[c_prev][c_curr]
                nf[j][1] = min(v3, v4)
        f = nf
        
    ans = min(min(f[j][0], f[j][1]) for j in range(m + 1))
    print(f"{ans:.2f}")

if __name__ == '__main__':
    main()