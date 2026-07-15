n, m = map(int, input().split())
values = [int(input()) for _ in range(n)]

window_sum = sum(values[:m])
answer = window_sum

for right in range(m, n):
    window_sum += values[right]
    window_sum -= values[right - m]
    answer = min(answer, window_sum)

print(answer)
