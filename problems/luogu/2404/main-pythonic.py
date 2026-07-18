n = int(input())
path = []
answers = []

def dfs(remaining, minimum):
    if remaining == 0:
        if len(path) > 1:
            answers.append("+".join(map(str, path)))
        return

    for value in range(minimum, remaining + 1):
        path.append(value)
        dfs(remaining - value, value)
        path.pop()

dfs(n, 1)
print(*answers, sep="\n")
