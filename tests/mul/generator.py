import random

def rand():
    return random.randint(0, 10)

file = open('in', 'w');
for i in range(10):
    a = 1
    b = 1
    for j in range(10):
        a = a * 10 + rand()
        b = b * 10 + rand()
    if rand() % 2 == 0:
        a = a * -1;
    if rand() % 2 == 0:
        b = b * -1;
    c = a * b
    file.write(str(a) + " " + str(b) + " " + str(c) + "\n")

