make merge
for i in 1 10 100 1000 10000 100000 1000000 10000000
do
	echo $i
	time ./merge $i
done
