standard="-std=c99 -pedantic"

projectName=nodes


if test -f $projectName.test; then
	rm $projectName.test
fi

if test -f o/; then
	rm o/*.o
fi


gcc $standard ../string/string.c $projectName.test.c $projectName.c -c
if test -f $projectName.o; then
	mv *.o o/
fi
gcc $standard o/string.o o/$projectName.test.o o/$projectName.o -o $projectName.test

./$projectName.test