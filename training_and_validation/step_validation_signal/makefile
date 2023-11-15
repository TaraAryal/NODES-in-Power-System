# Filename:       makefile
# Written by:     Niranjan Bhujel
# Date:           Nov-15-2023 12:05:43


CC          	= gcc
OUT             = -o 
RM          	= rm

CFLAGS			= 
CFLAGS      	+= -O2 
CFLAGS      	+= -lm
CFLAGS			+= -fPIC
CFLAGS      	+= -DRT=RT
CFLAGS      	+= -DUSE_RTMODEL
CFLAGS      	+= -DMAT_FILE=1

LDFLAGS         = -lm
SOURCES_MAIN    = Frequency_step_main.c
SOURCES     	= Frequency_step_interface.c 
SOURCES         +=sim_code/Frequency_step.c
SOURCES         +=sim_code/Frequency_step_data.c
SOURCES         +=sim_code/rtGetInf.c
SOURCES         +=sim_code/rtGetNaN.c
SOURCES         +=sim_code/rt_logging.c
SOURCES         +=sim_code/rt_nonfinite.c


OBJECT_MAIN		= Frequency_step_main.o
OBJECTS     	= $(SOURCES:.c=.o)

EXECS       	= $(SOURCES:%.c=%)

TARGET			= Frequency_step_main

SHARED_LIB		= Frequency_step_lib.so

stop_time 		= -1


.PHONY: all
all: $(OBJECT_MAIN) $(OBJECTS) 
	$(CC) $(CFLAGS) $(OBJECT_MAIN) $(OBJECTS) $(OUT) $(TARGET)

.PHONY: shared_lib
shared_lib: $(OBJECTS)
	$(CC) -fPIC -shared $(CFLAGS) $(OBJECTS) $(OUT) $(SHARED_LIB)

.c.o:
	$(CC) -c $(CFLAGS) $< $(OUT) $@

.o.: 
	$(CC) $^ $(LDFLAGS) $(OUT) $@

run: all
	./$(TARGET) $(stop_time) $(decimation)



	
.PHONY: clean
clean:
	-@ $(RM) $(OBJECT_MAIN)
	-@ $(RM) $(OBJECTS) 
	-@ $(RM) $(TARGET)
	-@ $(RM) $(SHARED_LIB)