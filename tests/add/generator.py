import random

def rand():
    return random.randint(0, 10)

file = open('in', 'w');

def operation(a, b):
    return a + b;

def create_test(x):
    a = str(rand() % 9 + 1)
    b = str(rand() % 9 + 1)
    for j in range(x):
        a += str(rand())
        b += str(rand())
    a = int(a)
    b = int(b)
    if rand() % 2 == 0:
        a = a * -1;
    if rand() % 2 == 0:
        b = b * -1;
    c = operation(a, b)
    file.write(str(a) + " " + str(b) + " " + str(c) + "\n")

# small
for i in range(10): 
    create_test(2)
    
# medium
for i in range(10):
    create_test(100)

# large
for i in range(10):
    create_test(100000)
