#!/usr/bin/python
# coding=utf-8
from io import open as f
#from io import close as io_close
from sys import argv, exit
import os
import shutil

S_PREFIX = 'temp_s_'
Q_PREFIX = 'temp_q_'
TEMP_DIRNAME = './temp'
CURR_DIR = '.'
SHARD_SIZE = 1000000

"""
Takes a fixed format file. Populates a result dict while reading input file line by line.
"""
def proccess_input(input_file):
    result = {}

    print( 'proccessing input file' )
#    print( input_file.readlines() )
    for line in input_file.readlines():        
        num_id = line[:9]
        data = line[10:].strip( '\n' )
        result.setdefault( num_id, [] ).append( data )
        
    return result

"""
Cleans up the temp dir.
"""
def clean():
    print( "Cleaning up the temp dir" )
    shutil.rmtree( TEMP_DIRNAME )
    os.mkdir('temp')

"""
Compares two files and returns it an a predefined manner.
fd_a: file descriptor
fd_b: file descriptor
res: touple of fds
"""
def compare( fd_a, fd_b ):
    size_a = os.stat( fd_a.name ).st_size
    size_b = os.stat( fd_b.name ).st_size
    print ( "size a is {} size b {}".format( size_a, size_b ) )
    result = ( fd_a, fd_b ) if ( size_a < size_b ) else ( fd_b, fd_a ) 
    return result

"""
Breaks down a file into shards with n entries each where n = SHARD_SIZE
in_fd: file-like object
prefix: string
result: int (number of shards)
"""
def make_parts( in_fd, prefix = 'unkn_' ):
    n = out_file_id = 0
    line = in_fd.readline()
    #print( os.getcwd() )
    os.chdir( TEMP_DIRNAME )
    out_fd = f ( '{}{}'.format( prefix, out_file_id ), mode = 'w' )
    while line:
        if n != 0 and ( n % SHARD_SIZE ) == 0:
            out_fd.close()
            out_file_id += 1
            out_fd = f ( '{}{}'.format( prefix, out_file_id ), mode = 'w' )

        out_fd.write( line )
        n += 1    
        line = in_fd.readline()

    out_fd.close()
    os.chdir( '..' )
    result = out_file_id if out_file_id > 0 else 1
    return result

"""
Performs Grace hash join build phase. Reads input files and then builds a partitioned hash file structure.
fd_a: file descriptor
fd_b: file descriptor
"""
def build( fd_a, fd_b ):
    clean()
    small_fd, big_fd = compare( fd_a, fd_b )
    print( "Breaking down the smaller file" )
    print( "Smaller file was broken into {} shards".format( make_parts( small_fd, prefix = S_PREFIX ) ) )
    print( "Breaking down the bigger file" ) 
    print( "Smaller file was broken into {} shards".format( make_parts( big_fd, prefix = Q_PREFIX ) ) )

"""
Performs s_hash contents and q_hash inner join
s_hash: dict of entries
q_hash: dict of entries
returns tuple ( int, list )
"""
def compare_hashes( s_hash, q_hash ):
    #return ( 0, [] )
    merged = []

    for k, s_v in s_hash.items():
        q_v = q_hash.get( k )
        if q_v != None:
            if len( s_v ) > 1:
                for e in s_v:
                    merged.append( '{2},{0},{1}\n'.format( e, q_v[0] , k ) )
            elif len( q_v ) > 1:
                for e in q_v:
                    merged.append( '{2},{0},{1}\n'.format( s_v[0], e, k ) )
            else:
                merged.append( '{2},{0},{1}\n'.format( s_v[0], q_v[0], k ) )

    return ( len( merged ), merged )


"""
Performs s_hash contents and all q partitions inner join
s_hash: dict of entries
out_fd: file-like object
returns int
"""
def scan_trough_qs( s_hash, out_fd):
    temp_files = os.listdir( CURR_DIR )
    q_files = [ s for s in temp_files if Q_PREFIX in s ]
    hash_match = 0
    for q in q_files:        
        q_hash = proccess_input( f( q ) )
        #print( '{}{}'.format ( s_hash, q_hash ) )
        m, merged = compare_hashes( s_hash, q_hash )
        hash_match += m

    out.writelines( merged )  
    return hash_match

"""
Performs Grace hash join scan phase. Sequentialy reads s_chunk_n files and compares its contents with contents from all q_chunk_n files.
"""
def scan( out_fd ):
    os.chdir( TEMP_DIRNAME )
    temp_files = os.listdir( CURR_DIR )
    s_files = [ s for s in temp_files if S_PREFIX in s ]
    hash_match = 0
    for s in s_files:        
        s_hash = proccess_input( f( s ) )
        hash_match += scan_trough_qs( s_hash, out_fd ) 
        
    print ( "Found {} entries".format( hash_match ) )

    #q_files = [ q for q in temp_files if Q_PREFIX in q ]

if __name__ == '__main__':
    if len( argv ) < 3:
        print ( '{0} usage syntax {0} <input a file name> <input b file name>'.format( 'simple.py' ) )
        quit()
    fname_a = argv[1]
    fname_b = argv[2]
    fname_res = 'result.csv'
    try:
        input_a = f( fname_a, buffering = 1 )
        input_b = f( fname_b, buffering = 1 )
        out = f( fname_res, mode = 'w' )
    except FileNotFoundError as e:
        print("Input file/-s not found")
        os.exit()

    build( input_a, input_b )
    scan( out )

    input_a.close()
    input_b.close()
    out.close() 

