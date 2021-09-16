if [ "$1" == "catch" ]; then
	if [ "$2" == "std" ]; then
		make catch_std && ./catch_build_std.exe
	else
		make catch && ./catch_build.exe
	fi
else
	make && ./a.out
fi
