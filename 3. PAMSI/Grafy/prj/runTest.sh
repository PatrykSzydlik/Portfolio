#! /bin/sh
IS_RAW=0;       # output type of route (0- good looking 1- raw)
GRAPH_TYPE=2;   # 0 - matrix,  1 - list , 2 - both
STARTING_VERTEX=0;
REPETITIONS=100;
# Build program
echo " Cleaning logs \n"
#make clean
#make cleanlog

echo " Building program \n"
make build

#start tests
echo " Running full test series \n"
for nvertices in 640
do
    for density in 25 50 75 100
    do  
    echo "     Testing graph with $nvertices vertices with $density % density \n" 
    ./exec/graphs -g $nvertices $STARTING_VERTEX $density gData.txt -r $REPETITIONS -o $nvertices\_$density\_route.txt $IS_RAW -t $GRAPH_TYPE 1>./log/$nvertices\_$density\_log.txt
    done
done
