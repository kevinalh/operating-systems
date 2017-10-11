# Santa Claus
from threading import *

elves = 0
reindeer = 0
santaSem = Semaphore(0)
reindeerSem = Semaphore(0)
elfTex = Semaphore(1)
mutex = Semaphore(1)


def reindeer_f():
    global reindeer
    mutex.acquire()
    reindeer += 1
    if reindeer == 9:
        santaSem.release()
    mutex.release()
    reindeerSem.acquire()
    # getHitched


def elves_f():
    global elves
    elfTex.acquire()
    mutex.acquire()
    elves += 1
    if elves == 3:
        santaSem.release()
    else:
        elfTex.release()
    mutex.release()

    # getHelp()

    mutex.acquire()
    elves -= 1
    if elves == 0:
        elfTex.release()
    mutex.release()


def santa_f():
    global reindeer
    while True:
        santaSem.acquire()
        mutex.acquire()
        if reindeer == 9:
            # prepareSleigh()
            for i in range(9):
                reindeerSem.release()
            reindeer -= 9
        elif elves >= 3:
            # helpElves()
            pass
        mutex.release()