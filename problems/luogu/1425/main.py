a, b, c, d = map(int, input().split())

start = a * 60 + b
end = c * 60 + d
hours, minutes = divmod(end - start, 60)

print(hours, minutes, end="")
