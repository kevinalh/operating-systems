# Dining Savages
from threading import *

n = 20
M = 10

servings = 0
mutex = Semaphore(1)
emptyPot = Semaphore(0)
fullPot = Semaphore(0)


def savage():
    global servings
    while True:
        mutex.acquire()
        if servings == 0:
            emptyPot.release()
            fullPot.acquire()
        servings -= 1
        mutex.release()
        # Eat
        print(current_thread().getName() + ": Eating")


def cook():
    while True:
        emptyPot.acquire()
        put_servings_in_pot(M)
        fullPot.release()


def put_servings_in_pot(m):
    global servings
    print("Putting servings in pot...")
    servings = m


t_savages = [Thread(target=savage, name="Savage " + str(x)) for x in range(n)]
t_cook = Thread(target=cook, name="Cook")

[x.start() for x in t_savages]
t_cook.start()