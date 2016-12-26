
        if req_type == 'BackendConnect': 
            self.check_phase( 'init', 'query' )
            self.state = 'query'
            b_url = tokens[4]
            b = self.backs.get( b_url )
            if b == None:
                b = Backend(b_url)
                self.backs['b_url'] = b
        elif req_type == 'BackendRequest':
            self.check_phase( 'query', 'query' )
            self.state = 'query'
            replica_id = tokens[4]
            rg = self.replica_groups.get( replica_id )
            if rg == None:
                rg = ReplicaGroup(replica_id)
                self.replica_groups[replica_id] = rg
            rg.proccess( event_tokens )
        elif req_type == 'BackendOk':
            self.check_phase( 'query', 'query' )
            self.state = 'query'
            replica_id = tokens[4]
            rg = self.replica_groups.get( replica_id )
            if rg == None:
                raise NoReplicaGroup
            rg.proccess( event_tokens )
            #rg.dec_req_count()
            rg.proccess( event_tokens )
        elif req_type == 'BackendError':
            self.check_phase( 'query', 'query' )
            self.state = 'query'
            replica_id, error_type = ( tokens[4], tokens[5] ) ####code to optimize
            rg = self.replica_groups.get( replica_id )
            if rg == None:
                raise NoReplicaGroup
            #rg.dec_req_count()
            rg.proccess( event_tokens )
        elif req_type == 'StartMerge':
            self.check_phase( 'query', 'merge' )
            self.state = 'merge'
        elif req_type == 'StartSendResult':
            self.check_phase( 'query', 'send' )
            self.state = 'send'
            self.start_send_req_ts = ts
        elif req_type == 'FinishRequest':
            pass         


