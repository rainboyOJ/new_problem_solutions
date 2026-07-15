n = int(input())

on_lights = set()

for _ in range(n):
    a_text, t_text = input().split()
    a = float(a_text)
    t = int(t_text)

    for k in range(1, t + 1):
        light = int(a * k)
        if light in on_lights:
            on_lights.remove(light)
        else:
            on_lights.add(light)

print(next(iter(on_lights)))
