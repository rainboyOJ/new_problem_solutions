import sys
from array import array
from collections import deque


data = iter(map(int, sys.stdin.buffer.read().split()))
n, left_jump, right_jump = next(data), next(data), next(data)
value = array("q", (next(data) for _ in range(n + 1)))
negative_infinity = -(1 << 60)
dp = array("q", [negative_infinity]) * (n + 1)
dp[0] = 0
queue = deque()
answer = negative_infinity

for i in range(left_jump, n + 1):
    candidate = i - left_jump
    if dp[candidate] != negative_infinity:
        while queue and dp[queue[-1]] <= dp[candidate]:
            queue.pop()
        queue.append(candidate)
    while queue and queue[0] < i - right_jump:
        queue.popleft()
    if queue:
        dp[i] = dp[queue[0]] + value[i]
    if i + right_jump > n:
        answer = max(answer, dp[i])

print(answer)
