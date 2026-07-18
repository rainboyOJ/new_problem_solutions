n = int(input())
numbers = list(map(int, input().split()))
unique_numbers = sorted(set(numbers))

print(len(unique_numbers))
print(*unique_numbers)
