#!/bin/bash

###################################
#          Configuration          #
###################################

# WARNING: if you launch to_launcher with docker all path described in this file
# need to be relative with the folder mounted
# Ex:
#   source
#       main.c
#   tests
#       to_tests
#           test1
#           test2
#           etc...
#       start_to_with_docker.sh
#       to_launcher.sh
#       test.sh
#   my_binary
#   Makefile
# test_file should be: tests/to_tests
# my_binary should be: ./my_binary

export my_binary="./my_objdump"
export sys_binary="objdump -fs"
export student_stdout_file="student_stdout"
export system_stdout_file="system_stdout"
export student_stderr_file="student_stderr"
export system_stderr_file="system_stderr"

# Define the folder where the tests are located
test_dir=("tests/objdump_test")

# Define the folder where the files needed for tests are located
export test_needed_file="tests/binary"

# Convert automatically the epitech standard error return code (84) to what you
# want if you need to test with an system binary that return normally 1 in exit case
# Can be disabled by setting convert_return_value to 0
export convert_return_value=1
export epitech_error_return_value="84"
export wanted_error_return_value="1"

if [ $convert_return_value -eq 1 ];
then
    echo "Return value are converted for you ($epitech_error_return_value => $wanted_error_return_value)"
fi
echo -e "/!\\ Remember to write error on error output !"

test_dir_ls=$(ls $test_dir)
test_nbr=$(echo $test_dir_ls | wc -w)
test_passed="0"

for item in ${test_dir_ls[*]}
do
    ./$test_dir/$item
    if [ "$(echo $?)" = "0" ];
    then
        test_passed=$(("$test_passed" + "1"))
    fi
done

echo -e "\nResult: $test_passed/$test_nbr test(s) passed"

rm $system_stdout_file $student_stdout_file $system_stderr_file $student_stderr_file
