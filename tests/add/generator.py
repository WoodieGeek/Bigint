import random

def rand():
    return random.randint(0, 1000000000000000000000000000000000000000000000000000000)

file = open('in', 'w');
for i in range(1000):
    a = rand() * rand() * rand();
    b = rand() * rand() * rand();
    if rand() % 2 == 0:
        a = a * -1;
    if rand() % 2 == 0:
        b = b * -1;
    c = a + b
    file.write(str(a) + " " + str(b) + " " + str(c) + "\n")

