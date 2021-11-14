#!/usr/bin/python3

import sys


NO_S    = 0
HAS_S   = 1


transitions = {
    NO_S: {
        ' ': NO_S,
        'a': NO_S,
        's': HAS_S,
    },
    HAS_S: {
        ' ': NO_S,
        'a': NO_S,
        's': HAS_S,
    },
}


outputs = {
    NO_S: {
        ' ': 0,
        'a': 0,
        's': 0,
    },
    HAS_S: {
        ' ': 1,
        'a': 0,
        's': 0,
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
    next_state = transitions.get(state, NO_S).get(normalize_input_char(next_char))
    output = outputs.get(state, NO_S).get(next_char, 'a')
    return next_state, output


def must_act(state: int, output: int):
    if state == HAS_S and output == 1:
        return True
    return False


def main():
    state = NO_S
    for line in sys.stdin:
        for next_char in line:
            new_state, output = state_transition(state, next_char)
            if must_act(state, output):
                print("+1")
            state = new_state


if __name__ == '__main__':
    main()
