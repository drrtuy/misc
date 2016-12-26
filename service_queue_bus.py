import random, pylab, math

class Job(object):
    def __init__(self, meanArrival, meanWork):
        #arrival rate of jobs
        self.arrival = random.expovariate(1.0/meanArrival)
        self.wk = random.gauss(meanWork, meanWork/2.0)
        self.timeQueued = None
    def interArrival(self):
        return self.arrival
    def work(self):
        return self.wk
    def queue(self, time):
        self.timeQueued = time
    def queuedTime(self):
        return self.timeQueued
    
class Passenger(Job):
    pass

class JobQueue(object):
    def __init__(self):
        self.jobs = []
    def arrive(self, job):
        self.jobs.append(job)
    def length(self):
        return len(self.jobs)
    def __str__(self):
        return self.__name__

class LIFO(JobQueue):
    def depart(self):
        try:
            job=self.jobs[0]
            self.jobs.remove(0)
            return job            
        except:
            print 'depart called with an empty queue'
            raise ValueError('EmptyQueue')

class FIFO(JobQueue):
    def depart(self):
        try:
            return self.jobs.pop(0)
        except:
            print 'depart called with an empty queue'
            raise ValueError('EmptyQueue')

class SRPT(JobQueue):
    def depart(self):
        try:
            leastIndx = 0
            for i in range(len(self.jobs)):
                if self.jobs[i].work < self.jobs[leastIndx].work:
                    leastIndx = i
            return self.jobs.pop(leastIndx)
        except:
            print 'depart called with an empty queue'
            raise ValueError('EmptyQueue')

class BusStop(FIFO):
    pass
    
class Bus(object):
    def __init__(self, capacity, speed):
        self.cap = capacity
        self.speed = speed
        self.onBus = 0
    def getSpeed(self):
        return self.speed
    def getLoad(self):
        return self.onBus
    def enter(self):
        if self.onBus < self.cap:
            self.onBus +=1
        else:
            raise ValueError('full')
    def leave(self):
        if self.onBus > 0:
            self.onBus -= 1
    def unload(self, num):
        while num > 0:
            self.leave()
            num -= 1

def simBus(bus,queueType, numStops = 6,loopLen = 1200, meanArrival = 90,meanWork = 10, simTime = 50000): 
    assert loopLen%numStops == 0
    stops = []
    for n in range(numStops):
        stops.append(queueType()) 
    time, totWait, totPassengers, lastArrival = [0.0]*4
    aveWaitTimes = []
    nextStop, busLoc, time = [0]*3
    nextJob = Passenger(meanArrival, meanWork)
    while time < simTime:
        #time tick
        time += 1
        for i in range(bus.getSpeed()):
            busLoc += 1
            if (busLoc)%(loopLen/numStops) == 0:
                break
        #passengers enter the bus
        if lastArrival + nextJob.interArrival() <= time:
            for stop in stops:
                stop.arrive(nextJob)
            nextJob.queue(time)
            lastArrival = time
            nextJob = Passenger(meanArrival, meanWork)
        if (busLoc)%(loopLen/numStops) == 0: #bus stop
            bus.unload(math.ceil(bus.getLoad()/float(numStops)))
            while stops[nextStop%numStops].length() > 0:
                try:
                    bus.enter()
                except:
                    break
                try:
                    p = stops[nextStop%numStops].depart()
                    totWait += time - p.queuedTime()
                    totPassengers += 1
                    time += p.work() #add some time ticks
                except:
                    pass
            try:
                aveWaitTimes.append(totWait/totPassengers)
            except ZeroDivisionError:
                aveWaitTimes.append(0.0)
            while lastArrival + nextJob.interArrival() <= time:
                for stop in stops:
                    stop.arrive(nextJob)
                nextJob.queue(time)
                lastArrival += nextJob.interArrival()
                nextJob = Passenger(meanArrival, meanWork)
            nextStop += 1
    leftWaiting = 0
    for stop in stops:
        leftWaiting += stop.length()
    return aveWaitTimes, leftWaiting
  
def lifoTest(capacities, speeds, numTrials):
    random.seed(0)
    for queueType in (FIFO,LIFO,SRPT):
        for cap in capacities:
            for speed in speeds:
                totWaitTimes = pylab.array([0.0]*500)
                totLeftWaiting = 0.0
                for t in range(numTrials):
                    aveWaitTimes, leftWaiting = simBus(Bus(cap, speed),queueType)
                    totWaitTimes += pylab.array(aveWaitTimes[:500])
                    totLeftWaiting += leftWaiting
                aveWaitTimes = totWaitTimes/numTrials
                leftWaiting = int(totLeftWaiting/numTrials)
                lab = 'Queue type' + str(queueType) + 'Spd = ' + str(speed) + ', Cap = ' + str(cap)+ ', Left = ' + str(leftWaiting)
                pylab.plot(aveWaitTimes, label = lab)
    pylab.xlabel('Stop Number')
    pylab.ylabel('Aggregate Average Wait Time')
    pylab.title('Impact of Bus Speed and Capacity')
    ymin, ymax = pylab.ylim()
    if ymax - ymin > 200:
        pylab.semilogy()
    pylab.ylim(ymin = 1.0)
    pylab.legend(loc = 'best')
        
def test(capacities, speeds, numTrials):
    #predictable behavior for debug
    #random.seed(0) 
    for cap in capacities:
        for speed in speeds:
            totWaitTimes = pylab.array([0.0]*500) #a place to save stats
            totLeftWaiting = 0.0
            for t in range(numTrials):
                aveWaitTimes, leftWaiting = simBus(Bus(cap, speed),FIFO)
                totWaitTimes += pylab.array(aveWaitTimes[:500])
                totLeftWaiting += leftWaiting
            aveWaitTimes = totWaitTimes/numTrials
            leftWaiting = int(totLeftWaiting/numTrials)
            lab = 'Spd = ' + str(speed) + ', Cap = ' + str(cap)\
                  + ', Left = ' + str(leftWaiting)
            pylab.plot(aveWaitTimes, label = lab)
    pylab.xlabel('Stop Number')
    pylab.ylabel('Aggregate Average Wait Time')
    pylab.title('Impact of Bus Speed and Capacity')
    ymin, ymax = pylab.ylim()
    if ymax - ymin > 200:
        pylab.semilogy()
    pylab.ylim(ymin = 1.0)
    pylab.legend(loc = 'best')

test([15, 30], [6, 10, 20], 20)
#lifoTest([15, 30], [6, 10, 20], 20)
pylab.show()

def simBus8(bus,queueType, numStops = 6,loopLen = 1200, meanArrival = 90,meanWork = 10, simTime = 50000): 
    assert loopLen%numStops == 0
    stops = []
    for n in range(numStops):
        stops.append(queueType())
    time, totWait, totPassengers, lastArrival = [0.0]*4
    aveWaitTimes = []
    nextStop, busLoc, time = [0]*3
    nextJob = Passenger(meanArrival, meanWork)
    while time < simTime:
        time += 1
        for i in range(bus.getSpeed()):
            busLoc += 1
            if (busLoc)%(loopLen/numStops) == 0:
                break
        if lastArrival + nextJob.interArrival() <= time:
            for stop in stops:
                stop.arrive(nextJob)
            nextJob.queue(time)
            lastArrival = time
            nextJob = Passenger(meanArrival, meanWork)
        if (busLoc)%(loopLen/numStops) == 0:
            bus.unload(math.ceil(bus.getLoad()/float(numStops)))
            while stops[nextStop%numStops].length() > 0:
                try:
                    bus.enter()
                except:
                    break
                try:
                    p = stops[nextStop%numStops].depart()
                    totWait += time - p.queuedTime()
                    totPassengers += 1
                    time += p.work()
                except:
                    pass
            try:
                aveWaitTimes.append(totWait/totPassengers)
            except ZeroDivisionError:
                aveWaitTimes.append(0.0)
            while lastArrival + nextJob.interArrival() <= time:
                for stop in stops:
                    stop.arrive(nextJob)
                nextJob.queue(time)
                lastArrival += nextJob.interArrival()
                nextJob = Passenger(meanArrival, meanWork)
            nextStop += 1
    leftWaiting = 0
    for stop in stops:
        leftWaiting += stop.length()
#    return aveWaitTimes, leftWaiting
    return totPassengers/leftWaiting
