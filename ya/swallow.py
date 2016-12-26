# coding=utf-8
#from io import FileIO as f
from io import open as f
from sys import argv
#use gc module for memory cleansing
#from memory_profiler import profile
#from pympler import asizeof, muppy, refbrowser

#import cProfile

#for careful reviewers! Globals are ugly but it`ll do the trick nevertheless

class NoReplicaGroup(Exception):
    pass

class SwallowBaseObject():
    """
    Abstract class.
    """
    def __init__(self, rg_id):
        self.id = rg_id

    def proccess(self, tokens):
        ts = tokens[0]  ####code to optimize
        req_id = tokens[1] 
        req_type = tokens[2]
        getattr( self, req_type )( tokens )

    def StartRequest(self, tokens):
        pass

    def BackendConnect(self, tokens):
        pass

    def BackendRequest(self, tokens):
        pass

    def BackendError(self, tokens):
        pass

    def BackendOk(self, tokens):
        pass

    def StartSendResult(self, tokens):
        pass

    def FinishRequest(self, tokens):
        pass

class Request(SwallowBaseObject):
    """
    This class represents one particular request from a log.     
    """
    def __init__(self):
        self.id = ''
        self.replica_groups = {}
        self.start_proc_req_ts = 0
        self.start_send_req_ts = 0
        self.send_req_time = 0
        
    def StartRequest(self, tokens):
        ts = tokens[0]
        req_id = tokens[1]
        self.id = req_id
        self.start_proc_req_ts = int( ts )

    def BackendConnect(self, tokens):
        replica_id = tokens[3]
        b_url =  tokens[4]
        rg = self.replica_groups.get( replica_id )
        if rg == None:
            rg = ReplicaGroup()
        self.replica_groups[replica_id] = rg
        rg.proccess( tokens )

    def BackendRequest(self, tokens):
        replica_id = tokens[3]
        rg = self.replica_groups.get( replica_id )
        rg.proccess( tokens )

    def BackendError(self, tokens):
        replica_id = tokens[3]
        rg = self.replica_groups.get( replica_id )
        if rg == None:
            raise NoReplicaGroup
        rg.proccess( tokens )        

    def BackendOk(self, tokens):
        replica_id = tokens[3]
        rg = self.replica_groups.get( replica_id )
        if rg == None:
            raise NoReplicaGroup
        rg.proccess( tokens )

    def StartMerge(self, tokens):
        if not self._rg_got_all_data():
            global_stats = globals().get( 'stats' )
            global_stats['rg_answer_miss'] += 1              

    def StartSendResult(self, tokens):
        ts = tokens[0]
        self.start_send_req_ts = int( ts )

    def FinishRequest(self, tokens):
        proc_req_time = self._calc_proc_time( tokens )

        global_stats = globals().get( 'stats' )

        if proc_req_time > global_stats.get( 'max_req_proc_time' ):
            global_stats['max_req_proc_time'] = proc_req_time 

        self.send_req_time = self._calc_send_time( tokens )
        # the last one from the longest sent time Requests list

        max_send_times = globals().get( 'max_req_send_times' )

        top_sent_looser = max_send_times[-1] if len( max_send_times ) > 0 else self 
        if top_sent_looser.send_req_time <= self.send_req_time:
            self._sort_send_times()
        else:
            self.replica_groups = {}
            curr_reqs = globals().get( 'curr_reqs' )
            del curr_reqs[self.id]

    def _calc_proc_time(self, tokens):
        stop_proc_req_ts = int( tokens[0] )
        return stop_proc_req_ts - self.start_proc_req_ts

    def _calc_send_time(self, tokens):
        stop_proc_req_ts = int( tokens[0] )
        return stop_proc_req_ts - self.start_send_req_ts

    def _sort_send_times(self):        
        max_send_times = globals().get( 'max_req_send_times' )
        max_send_times.append( self ) 
        if len( max_send_times ) > 10:
            max_send_times.sort( key = lambda r: r.send_req_time, reverse = True)
            req_id = max_send_times[-1].id
            curr_reqs = globals().get( 'curr_reqs' )
            del curr_reqs[self.id]
            del max_send_times[-1]

    def _rg_got_all_data(self):
        for rg_id,rg in self.replica_groups.iteritems():
            if rg and rg.has_open_connects != 0:
                return False
        return True
 
class ReplicaGroup(SwallowBaseObject):
    """
    This class represents a ReplicaGroup that proccess a frontend request. 
    The instance exists while serving a Request only.
    """
    def __init__(self):
        self.id = ''
        self.has_open_connects = False
        self.backs = globals().get( 'backends' )
        self.last_backend_url = ''

    def BackendConnect(self, tokens):
        replica_id = tokens[3]
        b_url = tokens[4]

        self.id = replica_id
        self.has_open_connects = True
        b = self.backs.get ( b_url )
        if b == None:
            b = Backend()
        self.last_backend_url = b_url
        b.proccess( tokens )

    def BackendRequest(self, tokens):
        self.has_open_connects = True
        b = self.backs.get ( self.last_backend_url )
        b.proccess( tokens )

    def BackendError(self, tokens):        
        b = self.backs.get ( self.last_backend_url )
        b.proccess( tokens )

    def BackendOk(self, tokens):
        self.has_open_connects = False

class Backend(SwallowBaseObject):
    """
    This class represents a Backend that serves Request for a ReplicaGroup. 
    """
    def __init__(self):
        self.url = ''
        self.backs = globals().get( 'backends' )
        self.reqs_number = 0
        self.errors = {}

    def BackendConnect(self, tokens):
        b_url = tokens[4]
        self.url = b_url
        b = self.backs.get ( b_url )
        if b == None:
            self.backs[b_url] = self

    def BackendRequest(self, tokens):
        self.reqs_number += 1

    def BackendError(self, tokens):
        error_text = tokens[4]

        if self.errors.get(error_text) != None:
            self.errors[error_text] += 1
        else:
            self.errors[error_text] = 1

def runtime():
    with f( fname ) as fd:
        line = fd.readline()
        while line:            
            tokens = line.strip('\n').split('\t') #ugly thing
            req_id = tokens[1]
            req_type = tokens[2]
            req = curr_reqs.get( req_id )
            if req == None:
                req = Request()
            curr_reqs[req_id] = req
            req.proccess( tokens )
            line = fd.readline()

if __name__ == '__main__':
    curr_reqs = {}
    backends = {}
    stats = {}
    stats['max_req_proc_time'] = 0 #for 95 percentile
    stats['rg_answer_miss'] = 0 #for the 4th question 
    max_req_send_times = [] #list of Requests

    fname = argv[1]
    backend_stats = True #if argv[2] else False

    runtime()

    if backend_stats == True:
        print '\nСтатистика по backend-ам'
        for un, b in backends.iteritems():
            print '\n backend url {0}'.format( b.url )
            print '     количество запросов {0}'.format( b.reqs_number )
            for e,n in enumerate( b.errors.iteritems() ):
                if not e:
                    print ' количество и тип ошибок '
                print '     Тип ошибки \'{0}\' количество {1}'.format( *n )
    

    print '95ый процентиль времени обработки процессов равен {0} сек'.format( stats['max_req_proc_time'] * 0.95 * 1e-6 )

    print '\nколичество запросов с неполным набором собранных с ГР данных  {0}'.format( stats['rg_answer_miss'] )

    print '\n10 запросов с наиболее продолжительной длительностью фазы отправки данных'
    for r in max_req_send_times:
        print '     Идентификатор запроса {0} длительность фазы отправки запроса {1}'.format( r.id, r.send_req_time * 1e-6 )         
