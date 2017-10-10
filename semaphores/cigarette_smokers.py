# Generalized Cigarette smokers problem
from threading import *

agentSem = Semaphore(1)
mutex = BoundedSemaphore(1)

tobacco = Semaphore(0)
paper = Semaphore(0)
match = Semaphore(0)

tobaccoSem = Semaphore(0)
paperSem = Semaphore(0)
matchSem = Semaphore(0)

# Scoreboard
nTobacco = nPaper = nMatch = 0


def agent_a():
    agentSem.acquire()
    tobacco.release()
    paper.release()


def agent_b():
    agentSem.acquire()
    paper.release()
    match.release()


def agent_c():
    agentSem.acquire()
    tobacco.release()
    match.release()


def pusher_a():
    """
    If the pusher comes into the room and finds
    another ingredient on the table, it will wakeup
    the corresponding smoker. Else, it will just
    leave the ingredient on the table and leave.
    """
    global nPaper, nMatch, nTobacco
    tobacco.acquire()
    mutex.acquire()

    if nPaper > 0:
        nPaper -= 1
        matchSem.release()
    elif nMatch > 0:
        nMatch -= 1
        paperSem.release()
    else:
        nTobacco += 1

    mutex.release()


def pusher_b():
    global nPaper, nMatch, nTobacco
    match.acquire()
    mutex.acquire()

    if nPaper > 0:
        nPaper -= 1
        tobaccoSem.release()
    elif nTobacco > 0:
        nTobacco -= 1
        paperSem.release()
    else:
        nMatch += 1

    mutex.release()


def pusher_c():
    global nPaper, nMatch, nTobacco
    paper.acquire()
    mutex.acquire()

    if nTobacco > 0:
        nTobacco -= 1
        matchSem.release()
    elif nMatch > 0:
        nMatch -= 1
        tobaccoSem.release()
    else:
        nPaper += 1

    mutex.release()


def smoker_a():
    matchSem.acquire()
    # Make cigarette
    agentSem.release()
    # Smoke cigarette


def smoker_b():
    tobaccoSem.acquire()
    # Make cigarette
    agentSem.release()
    # Smoke cigarette


def smoker_c():
    paperSem.acquire()
    # Make cigarette
    agentSem.release()
    # Smoke cigarette