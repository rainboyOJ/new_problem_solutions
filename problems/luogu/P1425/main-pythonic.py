a, b, c, d = map(int, input().split())
print(*divmod(c * 60 + d - (a * 60 + b), 60), end='')
