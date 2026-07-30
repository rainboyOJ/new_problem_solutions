light_count, person_count = map(int, input().split())

# 1 号操作后所有灯关闭；True 表示后来被切换为打开。
is_open = [False] * (light_count + 1)
for person in range(2, person_count + 1):
    for light in range(person, light_count + 1, person):
        is_open[light] = not is_open[light]

closed_lights = (str(light) for light in range(1, light_count + 1) if not is_open[light])
print(",".join(closed_lights))
