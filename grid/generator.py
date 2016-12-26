#!/usr/bin/python
# coding=utf-8
from io import open as f
from sys import argv
from random import choice, randrange
from string import ascii_uppercase, digits 

def get_tuple():
    l = ascii_uppercase + digits
    return '{0}{1}{2}{3}'.format( choice( l ), choice( l ), choice( l ), choice( l ) ) 

def get_rand_val():
    return '{0}-{1}-{2}'.format( get_tuple(), get_tuple(), get_tuple() )        

if __name__ == '__main__':
    if len( argv ) < 2:
        print ( '{0} usage syntax {0} <count>'.format( 'generator.py' ) )
        quit()

for n in range( int( argv[1] ) ): #'EKH3-5IDH-DNUK'
    print( '{:0>9},{}'.format( randrange(1000000), get_rand_val() ) )
