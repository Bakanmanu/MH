#!/bin/bash

rm results.txt

for FILE in $(ls datos_MDD)
do
    ./bin/main datos_MDD/$FILE >> "results.txt";
done 
