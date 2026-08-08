import sys


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    it = iter(data)
    N = next(it)
    V = next(it)
    v = [0] * (N + 1)
    w = [0] * (N + 1)
    parent = [0] * (N + 1)
    for i in range(1, N + 1):
        v[i] = next(it)
        w[i] = next(it)
        parent[i] = next(it)

    ans = 0
    for mask in range(1 << N):
        selected = [False] * (N + 1)
        ok = True
        for i in range(N):
            if mask & (1 << i):
                selected[i + 1] = True
        for i in range(1, N + 1):
            if not selected[i]:
                continue
            p = parent[i]
            while p != -1:
                if not selected[p]:
                    ok = False
                    break
                p = parent[p]
            if not ok:
                break
        if not ok:
            continue
        vol = 0
        val = 0
        for i in range(1, N + 1):
            if selected[i]:
                vol += v[i]
                val += w[i]
        if vol <= V:
            ans = max(ans, val)

    print(ans)


if __name__ == '__main__':
    solve()
