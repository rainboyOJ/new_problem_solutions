from datetime import date

start = date(*map(int, input().split()))
end = date(*map(int, input().split()))

print((end - start).days)
