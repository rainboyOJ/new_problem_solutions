numbers = list(map(int, input().split()))
answer = sum(numbers) * (2 ** (len(numbers) - 1))
print(answer)
