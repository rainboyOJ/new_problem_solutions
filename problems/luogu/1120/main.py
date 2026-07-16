import sys


data = iter(map(int, sys.stdin.buffer.read().split()))
n = next(data)
pieces = sorted((next(data) for _ in range(n)), reverse=True)
total = sum(pieces)
used = [False] * n


def possible(target):
    def dfs(used_count, current, start):
        if used_count == n:
            return True
        if current == target:
            return dfs(used_count, 0, 0)
        previous = -1
        for i in range(start, n):
            length = pieces[i]
            if used[i] or length == previous or current + length > target:
                continue
            used[i] = True
            if dfs(used_count + 1, current + length, i + 1):
                return True
            used[i] = False
            previous = length
            if current == 0 or current + length == target:
                return False
        return False

    return dfs(0, 0, 0)


for answer in range(pieces[0], total + 1):
    if total % answer == 0 and possible(answer):
        print(answer)
        break
