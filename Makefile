

test.exe: test.cpp ini_reader.obj
	cl $** -o $@

ini_reader.obj: ini_reader.cpp
	cl -c $** -o $@
