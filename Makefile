build:
	nim c -d:release --noMain --header --app:lib -o:./lib/dyn.so ./src/export.nim > /dev/null

static:
	nim --gcc.exe:musl-gcc --gcc.linkerexe:musl-gcc c -d:release --gc: none --noMain --header --passL:-static --app:lib -o:./lib/static.so ./src/export.nim > /dev/null

nim:
	nim c -d:release -o:./bin/ffi ./src/main.nim > /dev/null

cxx:
	g++ -o loader src/loader.cpp -static -ldl
	./loader