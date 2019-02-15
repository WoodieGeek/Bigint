#!/bin/bash
for dir in ./*
do
    echo $dir
    cd $dir
    make 
    cd ..
done
