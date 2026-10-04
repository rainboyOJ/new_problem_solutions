import sys
from collections import deque

def main() -> None:
    data = sys.stdin.buffer.read().split()
    n, m = int(data[0]), int(data[1])
    # 矩阵压成一维，格子 i 的行列为 (i // m, i % m)
    g = b"".join(data[2:])  # 各行拼接成一长串，共 n*m 个字符
    dist = [-1] * (n * m)
    q = deque()
    for i in range(n * m):
        if g[i] == 49:  # 字符 '1'：作为多源 BFS 的源点，距离 0
            dist[i] = 0
            q.append(i)
    while q:  # 多源 BFS：所有源点同层扩展，pop 时距离即最近 1 的曼哈顿距离
        u = q.popleft()
        r, c = divmod(u, m)
        d = dist[u] + 1
        for v in (u - m if r else -1, u + m if r < n - 1 else -1, u - 1 if c else -1, u + 1 if c < m - 1 else -1):
            if v >= 0 and dist[v] < 0:
                dist[v] = d
                q.append(v)
    # 按行拼好输出，避免逐格 join
    print("\n".join(" ".join(map(str, dist[i : i + m])) for i in range(0, n * m, m)))

main()
