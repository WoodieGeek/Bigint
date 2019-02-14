import random

def rand():
    return random.randint(0, 10000000000000000000000000000000);

file = open('in', 'w');
for i in range(1000):
    a = rand() * rand() * rand();
    b = rand() * rand() * rand();
    a = rand();
    b = rand() + 1;
    if rand() % 2 == 0:
        a = a * -1;
    if rand() % 2 == 0:
        b = b * -1;
    c = float(a) / float(b)
    file.write(str(a) + " " + str(b) + " " + str(c) + "\n")

