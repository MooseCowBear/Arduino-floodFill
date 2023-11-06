# Arduino-floodFill

Floodfill maze solving algorithm for Arduino. 

In its current form the floodfill function takes as input a 2d maze representation that is the number of squares in the maze x 4, where the length 4 array represents the square's north, south, east, west neighbors respectively. The maze is represented in this idiosyncratic way to align more closely with the information a robot will have as it traverses a maze, namely wall information. 

The main function does some work to convert 2d indices to their 1d counterparts before performing the flooding procedure. 

Compiled on Aruduino Uno R3.
