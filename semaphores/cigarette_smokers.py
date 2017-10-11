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
    while True:
        agentSem.acquire()
        tobacco.release()
        paper.release()


def agent_b():
    while True:
        agentSem.acquire()
        paper.release()
        match.release()


def agent_c():
    while True:
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
    while True:
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
    while True:
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
    while True:
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
    while True:
        matchSem.acquire()
        # Make cigarette
        agentSem.release()
        # Smoke cigarette
        print("A: Smoking cigarette")


def smoker_b():
    while True:
        tobaccoSem.acquire()
        # Make cigarette
        agentSem.release()
        # Smoke cigarette
        print("B: Smoking cigarette")


def smoker_c():
    while True:
        paperSem.acquire()
        # Make cigarette
        agentSem.release()
        # Smoke cigarette
        print("C: Smoking cigarette")


t_smoker_a = Thread(target=smoker_a, name='Smoker A')
t_smoker_b = Thread(target=smoker_b, name='Smoker B')
t_smoker_c = Thread(target=smoker_c, name='Smoker C')
t_pusher_a = Thread(target=pusher_a, name='Pusher A')
t_pusher_b = Thread(target=pusher_b, name='Pusher B')
t_pusher_c = Thread(target=pusher_c, name='Pusher C')
t_agent_a = Thread(target=agent_a, name='Agent A')
t_agent_b = Thread(target=agent_b, name='Agent B')
t_agent_c = Thread(target=agent_c, name='Agent C')

t_smoker_a.start()
t_smoker_b.start()
t_smoker_c.start()
t_pusher_a.start()
t_pusher_b.start()
t_pusher_c.start()
t_agent_a.start()
t_agent_b.start()
t_agent_c.start()