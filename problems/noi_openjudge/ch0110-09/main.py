input()
numbers = sorted(set(map(int, input().split())))

print(len(numbers))
print(*numbers)
