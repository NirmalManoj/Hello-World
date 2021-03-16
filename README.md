# Assignment 0
### Roll No: 2019111011, Nirmal Manoj C

## Instructions

Compile the code using the following commands
```mkdir build && cd build```

```cmake ..```

```make```

I have implemented three different solids as required for the assignment.

In the build folder, the program can be run using `./Hello-World`.

To select models 1, 2, and 3. A command line argument (1, 2, or 3) can be passed along while calling the program. If no argument is specified, the program will ask to choose the corresponding model in CLI and it can be selected.


### Controls

1. To move camera the following keys can be used.
    W - Move along negative z axis
    S - Move along positive z axis
    A - Move along negative x axis
    D - Move along positive x axis
    E - Move along positive y axis
    R - Move along negative y axis

2. To move the object, the following  keys can be used.
    I - Move along negative z axis
    K - Move along positive z axis
    J - Move along negative x axis
    L - Move along positive x axis
    O - Move along positive y axis
    P - Move along negative y axis

3. There are three different pre-decided orientations as required by the assignment. They can be selected using keys F7, F8, and F9.

4. In order to make object spin along any one axis, use `Left Shift` and to stop spinning use `Left Ctrl`.

5. To revolve the camera around the object, use `Right Shift` and to stop it revolving us `Right Ctrl`.