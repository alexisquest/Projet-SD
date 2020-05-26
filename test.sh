#!/bin/bash


for dim in {5..50..5}
do
	for dif in {1..91..10}
	do
		for nbcl in {2..16..2}
		do
			var="$dim $nbcl $dif"
			for exo in {2,1,0}
			do
				var+=$(./floodit_partie1 $dim $nbcl $dif 1 $exo 0)
			done
			echo $var >> resultattest.txt
		done
	done
done
