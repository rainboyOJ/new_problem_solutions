numbers = list(map(int, input().split()))
numbers.pop()

numbers.reverse()

print(*numbers)
