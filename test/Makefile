INC = /I googletest\include
LINK= googletest\lib\gtest.lib googletest\lib\gtest_main.lib

test1.exe : test1.cpp ..\ini_reader.obj
	cl.exe $(LINK) $** $(INC) /Fe$@ /link/SUBSYSTEM:CONSOLE 
