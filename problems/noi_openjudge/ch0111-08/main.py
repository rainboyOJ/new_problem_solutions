number_count = int(input())
numbers = {int(input()) for _ in range(number_count)}

print(*sorted(numbers))
