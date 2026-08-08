n = int(input())
s = input().strip()
table = str.maketrans(
    {chr(ord("a") + i): chr(ord("a") + (i + n) % 26) for i in range(26)}
)
print(s.translate(table))
