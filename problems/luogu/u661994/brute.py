import sys


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    it = iter(data)
    N = next(it)
    V = next(it)
    M = next(it)
    items = []
    for _ in range(N):
        v = next(it)
        w = next(it)
        p = next(it)
        items.append((v, w, p))

    ans = 0

    def dfs(idx: int, vol: int, weight: int, val: int) -> None:
        nonlocal ans
        if vol > V or weight > M:
            return
        if idx == N:
            ans = max(ans, val)
            return
        v, w, p = items[idx]
        dfs(idx + 1, vol, weight, val)
        dfs(idx + 1, vol + v, weight + w, val + p)

    dfs(0, 0, 0, 0)
    print(ans)


if __name__ == '__main__':
    solve()
