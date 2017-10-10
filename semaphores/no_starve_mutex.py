# No-starve mutex
from threading import *
from lightswitch import LightSwitch

room1 = room2 = 0
mutex = Semaphore(1)
# Turnstiles
t1 = Semaphore(1)
t2 = Semaphore(0)


def no_starve():
    global room1, room2

    mutex.acquire()
    room1 += 1
    mutex.release()

    t1.acquire()
    room2 += 1

    mutex.acquire()
    room1 -= 1
    if room1 == 0:
        mutex.release()
        t2.release()
    else:
        mutex.release()
        t1.release()

    t2.acquire()
    room2 -= 1

    # Critical section

    if room2 == 0:
        t1.release()
    else:
        t2.release()
