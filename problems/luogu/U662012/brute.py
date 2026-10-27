import sys


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    it = iter(data)
    N = next(it)
    V = next(it)
    f = []
    for _ in range(N):
        K = next(it)
        points = []
        for __ in range(K):
            x = next(it)
            y = next(it)
            points.append((x, y))
        vals = [0] * (V + 1)
        for x in range(V + 1):
            if x <= points[0][0]:
                vals[x] = points[0][1]
            elif x >= points[-1][0]:
                vals[x] = points[-1][1]
            else:
                for j in range(len(points) - 1):
                    x1, y1 = points[j]
                    x2, y2 = points[j + 1]
                    if x1 <= x <= x2:
                        t = (x - x1) / (x2 - x1)
                        vals[x] = int(y1 + t * (y2 - y1))
                        break
        f.append(vals)

    ans = 0

    def dfs(idx: int, remaining: int, cur_val: int) -> None:
        nonlocal ans
        if idx == N:
            ans = max(ans, cur_val)
            return
        for x in range(remaining + 1):
            dfs(idx + 1, remaining - x, cur_val + f[idx][x])

    dfs(0, V, 0)
    print(ans)


if __name__ == '__main__':
    solve()
