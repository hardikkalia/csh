# Description

# Assumptions
 Specification[4]:peek
    User can use one flag multiple times. Example:
        peek -a -a and peek -al -l are valid
Specification[5]: pastevents
    History will be stored in history.txt file
    ; separated commands will be stored separately. echo "Hello" ; echo "World" will add 2 entries to the history - echo "Hello" and echo "World"