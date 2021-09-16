if [ "$1" == "catch" ]; then
	if [ "$2" == "std" ]; then
		# ./run.sh catch std
		make catch_std && ./catch_build_std.exe
	else
		# ./run.sh catch
		make catch && ./catch_build.exe
	fi
else
	# ./run.sh
	make && ./a.out
fi
