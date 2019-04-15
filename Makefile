all: serial parallel

performance_test: graph_processor.c graph_processor.h stopwatch.c stopwatch.h performance_test.c
	gcc -Wall -Werror -pthread -O3 graph_processor.c stopwatch.c performance_test.c -o fw_performance_test

tests: graph_processor.c graph_processor.h file_interface.c file_interface.h tests.c
	gcc -Wall -Werror -pthread -O3 graph_processor.c file_interface.c tests.c -o tests 

serial: graph_processor.c graph_processor.h file_interface.c file_interface.h main_serial.c
	gcc -Wall -Werror -pthread -O3 graph_processor.c file_interface.c main_serial.c -o fw_serial 

parallel: graph_processor.c graph_processor.h file_interface.c file_interface.h main_parallel.c
	gcc -Wall -Werror -pthread -O3 graph_processor.c file_interface.c main_parallel.c -o fw_parallel 

clean:
	rm -f fw_serial fw_parallel
	
