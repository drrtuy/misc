#!/usr/bin/python
# coding=utf-8
from io import open as f
from sys import argv 

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

if __name__ == '__main__':
    if len( argv ) < 3:
        print ( '{0} usage syntax {0} <input a file name> <input b file name>'.format( 'simple.py' ) )
        quit()
    fname_a = argv[1]
    fname_b = argv[2]
    fname_res = 'result.csv'
    input_a = f( fname_a, buffering = 1 )
    input_b = f( fname_b, buffering = 1 )
    out = f( fname_res, mode = 'w' ) 
    dict_a = {}
    dict_b = {}
    merged = []
    
    dict_a = proccess_input( input_a )
    dict_b = proccess_input( input_b )
    """
    print( 'dict_a')
    print( dict_a )
    print( 'dict_b')
    print( dict_b )
    """
    for k, a_v in dict_a.items():
        b_v = dict_b.get( k )
        if b_v != None:
            if len( a_v ) > 1:
                for e in a_v:
                    merged.append( '{2},{0},{1}\n'.format( e, b_v[0] , k ) )
            elif len( b_v ) > 1:
                for e in b_v:
                    merged.append( '{2},{0},{1}\n'.format( a_v[0], e, k ) )
            else:
                merged.append( '{2},{0},{1}\n'.format( a_v[0], b_v[0], k ) )

    out.writelines( merged )
    print( 'Files {} and {} contents was merged. Check {}'.format( fname_a, fname_b, fname_res ) )
    

