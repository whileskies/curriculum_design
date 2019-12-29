obj = AddList.o Hash.o ArrayHash.o

Main: $(obj)
	g++ -g -o $@ $^
..c.o:
	g++ -g -c $<

clean:
	rm $(obj)