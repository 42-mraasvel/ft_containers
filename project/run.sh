if [ "$1" == "catch" ]; then
	if [ "$2" == "std" ]; then
		# ./run.sh catch std
		make catch_std && ./catch_std.out
	else
		# ./run.sh catch
		make catch && ./catch.out
	fi
else
	# ./run.sh
	make && ./a.out
fi
