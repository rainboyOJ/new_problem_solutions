heights = list(map(int, input().split()))
taotao = int(input())

reach = taotao + 30
answer = sum(1 for height in heights if height <= reach)

print(answer, end="")
