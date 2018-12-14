import random

f = open("main.in", "w")
f.write("30000 1\n")
status = []

for num in range(1, 10000):
    arrive = random.randint(1, 10000000)
    departure = random.randint(1, 10000000)
    if arrive > departure:
        arrive, departure = departure, arrive
    status.append(('A', num, arrive))
    status.append(('D', num, departure))

status = sorted(status, key=lambda x: x[2])

for each in status:
    f.write("%s %d %d\n" % (each[0], each[1], each[2]))

f.write("E 0 0")
f.close()