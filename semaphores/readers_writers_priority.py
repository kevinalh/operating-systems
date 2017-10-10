# Readers-Writers with Writer-priority
from threading import *
from lightswitch import LightSwitch

nr = 3000
nw = 10

database = 0

readSwitch = LightSwitch()
writeSwitch = LightSwitch()
noReaders = Semaphore(1)
noWriters = Semaphore(1)


def reader():
    noReaders.acquire()
    readSwitch.lock(noWriters)
    noReaders.release()

    # Reading
    print(database)

    readSwitch.unlock(noWriters)


def writer():
    writeSwitch.lock(noReaders)
    noWriters.acquire()

    # Critical section
    # The thread holds both noReaders and noWriters
    global database
    database += 1

    noWriters.release()
    writeSwitch.unlock(noReaders)


readers = [Thread(target=reader, name='Reader ' + str(i)) for i in range(nr)]
writers = [Thread(target=writer, name='Writer ' + str(i)) for i in range(nw)]

[x.start() for x in set().union(readers, writers)]