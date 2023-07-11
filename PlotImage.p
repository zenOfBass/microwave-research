set datafile separator ","
set view map
set pm3d at b map
set dgrid3d 200,200,2
splot "output.csv" u 1:2:3
