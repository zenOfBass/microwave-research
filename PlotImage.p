set datafile separator ","
set view map
set dgrid3d
splot "output.csv" using 1:2:3 with pm3d