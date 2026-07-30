number, required_count = map(int, input().split())
is_valid = number % 19 == 0 and str(number).count("3") == required_count
print("YES" if is_valid else "NO")
