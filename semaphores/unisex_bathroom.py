from threading import Semaphore
from lightswitch import LightSwitch


empty = Semaphore(1)
maleSwitch = LightSwitch()
femaleSwitch = LightSwitch()
maleMultiplex = Semaphore(3)
femaleMultiplex = Semaphore(3)
turnstile = Semaphore(1)


def female():
    turnstile.acquire()
    femaleSwitch.lock(empty)
    turnstile.release()

    femaleMultiplex.acquire()
    # Use the bathroom
    femaleMultiplex.release()

    femaleSwitch.unlock(empty)


def male():
    turnstile.acquire()
    maleSwitch.lock(empty)
    turnstile.release()

    maleMultiplex.acquire()
    # Use the bathroom
    maleMultiplex.release()

    maleSwitch.unlock(empty)