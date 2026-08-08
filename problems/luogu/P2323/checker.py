#!/usr/bin/env python3
import sys


def parse_input(path):
    with open(path, "r", encoding="utf-8") as f:
        data = f.read().strip().split()
    if not data:
        return None
    n = int(data[0])
    k = int(data[1])
    # 第三个数在原题里有歧义，这里只把后续实际读到的边作为准。
    pos = 3
    edges = []
    idx = 1
    while pos + 3 < len(data):
        a = int(data[pos])
        b = int(data[pos + 1])
        c1 = int(data[pos + 2])
        c2 = int(data[pos + 3])
        edges.append((a, b, c1, c2))
        pos += 4
        idx += 1
    return n, k, edges


def parse_output(path):
    with open(path, "r", encoding="utf-8") as f:
        lines = [line.strip() for line in f if line.strip()]
    if not lines:
        return None
    first = lines[0]
    if first == "-1":
        return -1, []
    cost = int(first)
    ans = []
    for line in lines[1:]:
        a, b = map(int, line.split())
        ans.append((a, b))
    return cost, ans


def validate(n, k, edges, output):
    if output is None:
        return False, "empty output"
    best_cost, ans = output
    if best_cost == -1:
        return True, "ok"
    if len(ans) != n - 1:
        return False, "wrong edge count"
    if ans != sorted(ans):
        return False, "edges not sorted by id"

    fa = list(range(n + 1))

    def find(x):
        while fa[x] != x:
            fa[x] = fa[fa[x]]
            x = fa[x]
        return x

    def unite(x, y):
        x = find(x)
        y = find(y)
        if x == y:
            return False
        fa[x] = y
        return True

    used = set()
    level1_cnt = 0
    max_cost = 0

    for idx, level in ans:
        if idx < 1 or idx > len(edges):
            return False, "edge id out of range"
        if idx in used:
            return False, "duplicate edge"
        if level not in (1, 2):
            return False, "invalid level"
        used.add(idx)

        u, v, c1, c2 = edges[idx - 1]
        if not unite(u, v):
            return False, "forms cycle"

        if level == 1:
            level1_cnt += 1
            max_cost = max(max_cost, c1)
        else:
            max_cost = max(max_cost, c2)

    root = find(1)
    for i in range(2, n + 1):
        if find(i) != root:
            return False, "not connected"

    if level1_cnt < k:
        return False, "not enough level1 roads"
    if max_cost != best_cost:
        return False, "first line does not match actual maximum cost"
    return True, "ok"


def main():
    if len(sys.argv) != 4:
        return 2

    n, k, edges = parse_input(sys.argv[1])
    user = parse_output(sys.argv[2])
    brute = parse_output(sys.argv[3])

    ok_user, msg_user = validate(n, k, edges, user)
    if not ok_user:
        print(msg_user, file=sys.stderr)
        return 1

    ok_brute, msg_brute = validate(n, k, edges, brute)
    if not ok_brute:
        print("brute invalid: " + msg_brute, file=sys.stderr)
        return 1

    if user[0] != brute[0]:
        print(f"best cost differs: user={user[0]}, brute={brute[0]}", file=sys.stderr)
        return 1

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
