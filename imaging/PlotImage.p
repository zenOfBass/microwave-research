set datafile separator ","
set view map
set pm3d at b map
set dgrid3d 200,200,2
set palette defined (0 0 0 0.5, 1 0 0 1, 2 0 0.5 1, 3 0 1 1, 4 0.5 1 0.5, 5 1 1 0, 6 1 0.5 0, 7 1 0 0, 8 0.5 0 0)
splot "output.csv" u 1:2:3
