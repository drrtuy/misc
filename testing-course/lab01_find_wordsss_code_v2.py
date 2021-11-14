#!/usr/bin/python3

import sys


OUTSIDE_WORD = 0
CURRENT_S = 1
FOUND_WORD = 2


transitions = {
    OUTSIDE_WORD: {
        ' ': OUTSIDE_WORD,
        'a': OUTSIDE_WORD,
        's': CURRENT_S,
    },
    CURRENT_S: {
        ' ': FOUND_WORD,
        'a': OUTSIDE_WORD,
        's': CURRENT_S,
    },
    FOUND_WORD: {
        ' ': OUTSIDE_WORD,
        'a': OUTSIDE_WORD,
        's': CURRENT_S,
    },
}


input_char_map = {
    ' ': ' ',
    '.': ' ',
    ',': ' ',
    '"': ' ',
    '\n': ' ',
    's': 's',
}


def normalize_input_char(next_char:str ):
    return input_char_map.get(next_char.lower(), 'a')


def state_transition(state: int, next_char):
    return transitions.get(state, OUTSIDE_WORD).get(normalize_input_char(next_char))


def main():
    state = OUTSIDE_WORD
    for line in sys.stdin:
        for next_char in line:
            state = state_transition(state, next_char)
            if state == FOUND_WORD:
                print("+1")


if __name__ == '__main__':
    main()
