apples, hours_per_apple, hours = map(int, input().split())
eaten = (hours + hours_per_apple - 1) // hours_per_apple
print(max(0, apples - eaten))
