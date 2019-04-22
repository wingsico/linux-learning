lib=libmylib.a
main=my_main
${main}: ${lib} my_main.o
	gcc -o $@ my_main.o -L. -lmylib
my_main.o: my_main.c my.h
	gcc -c $<
${lib}:	my_min.o my_max.o my_sum.o my_avg.o
	ar crv ${lib} $^
my_min.o: my_min.c
	gcc -c $<
my_max.o: my_max.c
	gcc -c $<
my_sum.o: my_sum.c
	gcc -c $<
my_avg.o: my_avg.c
	gcc -c $<
clean:
	rm -rf *.o ${lib} ${main} 