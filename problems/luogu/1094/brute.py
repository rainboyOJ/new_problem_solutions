import sys


def greedy(limit, prices):
    prices = sorted(prices)
    left, right = 0, len(prices) - 1
    answer = 0
    while left <= right:
        if prices[left] + prices[right] <= limit:
            left += 1
        right -= 1
        answer += 1
    return answer


data = list(map(int, sys.stdin.buffer.read().split()))
limit = data[0]
n = data[1]
prices = data[2:2 + n]

if n > 20:
    print(greedy(limit, prices))
else:
    used = [False] * n
    answer = n

    def dfs(groups):
        global answer
        if groups >= answer:
            return
        first = next((i for i, flag in enumerate(used) if not flag), -1)
        if first == -1:
            answer = groups
            return

        used[first] = True
        dfs(groups + 1)
        for j in range(first + 1, n):
            if not used[j] and prices[first] + prices[j] <= limit:
                used[j] = True
                dfs(groups + 1)
                used[j] = False
        used[first] = False

    dfs(0)
    print(answer)
