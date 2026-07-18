n = int(input())
answer = 0
left = 1

while left <= n:
    quotient = n // left
    right = n // quotient
    answer += quotient * (right - left + 1)
    left = right + 1

print(answer)
