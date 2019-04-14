all: serial parallel

serial: graph_processor.c graph_processor.h file_interface.c file_interface.h fw_serial.c
	gcc -Wall -Werror -pthread -O3 graph_processor.c file_interface.c fw_serial.c -o fw_serial 

parallel: graph_processor.c graph_processor.h file_interface.c file_interface.h fw_parallel.c
	gcc -Wall -Werror -pthread -O3 graph_processor.c file_interface.c fw_parallel.c -o fw_parallel 

clean:
	rm -f fw_serial fw_parallel
	
