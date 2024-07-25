# Description


---
# Assumptions

### Specification[4]: **peek**
- User can use one flag multiple times.  
`peek -a -a`  and  `peek -al -l` are valid
- Directories are printed in blue, files in white, and executables in green 

### Specification[5]: **pastevents**
- History will be stored in `history.txt` file
- `;` separated commands will be stored separately  
`echo Hello ; echo Hello World` adds 2 entries to `history.txt`
- background processes are not added to history

### Specification[6]: **background processes**
- While creating background commands, user can either give all background commands:  
    `sleep 5 & sleep 6 & sleep 7 &`  
    or give one foreground command at the end:   
    `sleep 5 & sleep 6 & echo "Lorem Ipsum"`

### Specification[7]: **proclore**
- The proclore function uses proc files to access process info.  
So the terminal must be running on a linux machine to use proclore

### Specification[9] **IO Redirection** 
- On using `<` , the  terminal reads the first line from the input file and takes it as the input

### Specification[12]: **activities**
- This command uses proc/stat files. So it must be used on linux systems only
- A process is displayed as stopped if its status is `T` is in the stat file. Otherwise it is shown as running

### Specification[13]: **signals** 
- Since `ctrl+D` sends an EOF character, it cannot terminate the terminal when a process is currently running.  
To terminate in such a state, first press `ctrl+C` and then `ctrl+D`

### Specification[15]: **neonate**
- Using `ctrl+C` or `ctrl+D` does not stop neonate. Press `x`
- On running `neonate -n 0`, the terminal continuously prints the pid of most recent process.
- It uses proc/loadavg files. So it must be used on linux systems only

### Specification[16]: **iMan**
- Prints out the Name, Synopsis and Description from man.he.net

