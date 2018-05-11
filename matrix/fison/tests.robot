*** Settings ***
Library           Process
Suite Teardown    Terminate All Processes    kill=True

*** Test Cases ***
Correct single matrix operand#1
    ${result} =    Run Process    echo '[5 5 5; 5 5 5]' | ./calc.x    shell=True    cwd=./
    Should Contain    ${result.stdout}  [ 5 5 5; 5 5 5 ]   
    ${result} =    Run Process    echo '[2;2;2;2;2;2;]' | ./calc.x    shell=True    cwd=./
    Should Contain    ${result.stdout}  [ 2; 2; 2; 2; 2; 2 ]   
Inconsistent row sizes
    ${result} =    Run Process    echo '[5 5 5; 5 5]' | ./calc.x    shell=True    cwd=./
    Should Contain    ${result.stderr}    Inconsistent matrices dimensions
    ${result} =    Run Process    echo '[5 5 5; 5 5 5 5]' | ./calc.x    shell=True    cwd=./
    Should Contain    ${result.stderr}    Inconsistent matrices dimensions
Incorrect syntax
    ${result} =    Run Process    echo '[2;2;2;2;2;2;]' | ./calc.x    shell=True    cwd=./
    Should Contain    ${result.stderr}  syntax error 
Correct matrix addition
    ${result} =    Run Process    echo '[5 5 5; 5 5 5]+[3 3 3; -1 -8 0]' | ./calc.x    shell=True    cwd=./
    Should Contain    ${result.stdout}  [ 8 8 8; 4 -3 5 ] 
Incorrect matrix addition
    ${result} =    Run Process    echo '[ 5 5; 5 5 5]+[3 3 3; 5 -1 -8 0]' | ./calc.x    shell=True    cwd=./
    Should Contain    ${result.stderr}  Inconsistent matrices dimensions 
