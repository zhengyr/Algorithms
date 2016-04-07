
http://www.cs.brandeis.edu/~storer/cs180/Assignments/BrandeisMap/Project.html

___________________________________________________________________


HOW TO COMPILE Map.c:

1.
Change to the map directory; for example, something like:
cd /Users/home/SRC/BrandeisMap

2.
Compile the assignment template code:
gcc -ansi -Wall -o Map Map.c


___________________________________________________________________


TO RUN:

1. Open MatLab, load Display.m, get rid of all windows except the one
   to run the program, and make that a little window in the lower left
   corner of the screen (just large enough so you can click on the run arrow).

2. Start Map, which opens a terminal window, and reposition and size the window
   so it is on the left side of the screen.

   OR: If the program was compiled without setting up the PATH
       variable at the beginning of the code,
       open a terminal window change directory to the Map folder,
       and and start Map from a command line by typine ./Map.

3. Now you can repeatedly run Map and then run Matlab to see the
   path on the Brandeis map.


___________________________________________________________________


PUBLIC FILES THAT SHOULD NOT BE MODIFIED:

aaaReadme.txt
This ile.

Assignment.pdf
AssignmentPart2.pdf
The assignment.

BrandeisMapLabeled.jpg
BrandeisMapLabeledCropped.jpg
Labeled and cropped versions of Brandeis map.

Display.m
DisplayCropped.m
MatLab program to display path on BrandeisMapLabeled or BrandeisMapLabeledCropped.

Map.h
Map data and parameters.

MapData.h
Functions to input the map data and compute time.

MapDataEdges.txt
MapDataVertices.txt
Map data files that are read in when the program starts.

MapInput.h
MapOutput.h
User input and output functions.

Project.html
Web page for this assignment.

Route.txt
RouteCropped.txt
Pixel coordinates of each edge on path to be used for plotting.

RouteEdges
Text file of the edges on the route that may be useful for debugging.

SampleOutputs
A folder with some sample outputs with the corresponding paths and maps.

Solutions.txt
Output from the assignment tests, using double precision to compute times.

___________________________________________________________________


PUBLIC FILES THAT ARE INTENDED TO BE MODIFIED:

Map
Executable application from compiling Map.c.

Map.c
Base code for the assignment that must be completed.

MapPATH.h
Path to the map folder; may need to change this (see the comment in the file).

Tour.h
Place code here for the assignment Part 2.