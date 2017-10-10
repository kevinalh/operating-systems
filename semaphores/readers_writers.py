# Readers-Writers
from threading import *
from lightswitch import LightSwitch

nr = 3000
nw = 10

database = 0

readSwitch = LightSwitch()
roomEmpty = Semaphore(1)
turnstile = Semaphore(1)


def reader():
    turnstile.acquire()
    turnstile.release()
    readSwitch.lock(roomEmpty)

    # Reading
    print(database)

    readSwitch.unlock(roomEmpty)


def writer():
    turnstile.acquire()
    roomEmpty.acquire()

    # Nobody in the room: Writing
    global database
    database += 1

    turnstile.release()
    roomEmpty.release()


readers = [Thread(target=reader, name='Reader ' + str(i)) for i in range(nr)]
writers = [Thread(target=writer, name='Writer ' + str(i)) for i in range(nw)]

[x.start() for x in set().union(readers, writers)]