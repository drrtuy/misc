import subprocess

SOLUTION_FILENAME = 'lab01_find_wordsss_code.py'
ABSTRACT_TEST_FILENAME = 'generated_test_sequences.txt'
PATH_PREFIX = '/git/misc/testing-course'

output_transducer = {
    '1': '+1\n',
    '0': '',
    'impossible': 'Z',
}

input_transducer = {
    '0': ' ',
    '1': 'a',
    '2': 's',
    'impossible': 'Z',
}


def iterate_transducer(test:str, transducer: dict, transducer_tuple_idx: int):
    result = ''
    for el in test.split():
        if len(el) == 0:
            continue
        result += transducer.get(
            el.split('/')[transducer_tuple_idx],
            output_transducer['impossible']
        )
    return result


def get_result_line(test: str, transducer):
    return iterate_transducer(test, transducer, 1)


def get_input_line(test: str, transducer):
    return iterate_transducer(test, transducer, 0)


def run_test(test_filename: str, solution_filename: str):
    with open(test_filename, 'r') as test_file:
        for test in test_file:
            expected_output = get_result_line(test, output_transducer)
            input_line = get_input_line(test, input_transducer)
            print(f'input {repr(input_line)}\t output {repr(expected_output)}', end=' ')
            output = ''
            p = subprocess.Popen(f'{PATH_PREFIX}/{solution_filename}',
                text=True,
                stdin=subprocess.PIPE,
                stdout=subprocess.PIPE,
            )
            (out, err) = p.communicate(input=input_line)
            try:
                assert(expected_output == out)
                print(' test pass')
            except (AssertionError):
                print(f'!!!TEST FAIL!!! expected output {repr(expected_output)}', end='')
                if len(output):
                    print(f' output {repr(output)}')
                else:
                    print(' no output or output is empty')


if __name__ == '__main__':
    run_test(ABSTRACT_TEST_FILENAME, SOLUTION_FILENAME)
