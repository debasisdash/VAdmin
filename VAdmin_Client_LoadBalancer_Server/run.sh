#!/bin/bash

########################################
#Author   : Debasis Dash               #
#Purpose  : This tool is developed for #
#           generating the load in the #
#           system                     #
#location : San Jose State University  #
######################################## 

touch data.txt
num=0
while [ $num -lt 50000 ]
    do
        echo "This is Testing Code" >> data.txt
        num=`expr $num + 1 `
    done

num2=0
while [$num -lt 50000]
    do
    val=`expr 2 + 2`
    val=`expr 2 - 2`
    val=`expr 2 * 2`
    val=`expr 2 / 2`
    echo "Total value : $val"
        num=`expr $num + 1 `
        done
echo "Completed with the writing ..Going to Read"

filename='data.txt'
filelines=`cat $filename`
echo Start
for line in $filelines ; 
do
    echo $line
done

