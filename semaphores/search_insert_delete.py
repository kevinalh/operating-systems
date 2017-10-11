# Search-insert-delete
from threading import *
from lightswitch import LightSwitch

searcherSwitch = LightSwitch()
inserterSwitch = LightSwitch()

inserter = Semaphore(1)
searcher = Semaphore(1)
deleter = Semaphore(1)

mutex = Semaphore(1)


def searcher_f():
    searcherSwitch.lock(searcher)
    # Search through list
    searcherSwitch.unlock(searcher)


def inserter_f():
    inserterSwitch.lock(deleter)
    inserter.acquire()
    # Insert into list
    inserter.release()
    inserterSwitch.unlock(deleter)


def deleter_f():
    deleter.acquire()
    inserter.acquire()
    searcher.acquire()
    # Delete from list
    searcher.release()
    inserter.release()
    deleter.release()