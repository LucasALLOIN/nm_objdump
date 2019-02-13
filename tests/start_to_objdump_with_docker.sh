#!/bin/bash

# The path mounted to docker to execute test: Must be root of your project
test_dir="/home/lucas/Documents/PSU_nmobjdump_2018"

# The test Bash script relative path to your project root
#Ex:
#   source
#       main.c
#   tests
#       test.sh
#   Makefile
#Sould be: tests/test.sh
test_script="tests/to_launcher.sh"

docker run -v $test_dir:/home/epitest -w /home/epitest epitechcontent/epitest-docker /home/epitest/$test_script
