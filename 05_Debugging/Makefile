all:
	gcc main.c -g -o range
test:
	gdb --args ./range 1 12 < gdb-script | grep @@@ | cmp correct1
	gdb --args ./range -100 100 3 < gdb-script2 | grep @@@ | cmp correct2
clean:
	rm range
