numbers = map(int, input().split())
print(*(f"{number:>8}" for number in numbers))
