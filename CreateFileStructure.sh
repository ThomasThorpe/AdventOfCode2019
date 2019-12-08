#!/bin/bash

for day in {1..25}
do
	mkdir Day$day
	cd Day$day
	for puzzle in {1..2}
	do
		mkdir Puzzle$puzzle
	done
	cd ..
done
