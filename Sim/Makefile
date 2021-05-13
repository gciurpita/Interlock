
	CPPFLAGS += -Wall -Werror

	Hdrs = *.h
    Objs = $(patsubst %.cpp, %.o, $(Srcs))
	Srcs  = $(shell echo *cpp)
	Targ = sim

# --------------------------------------------------------------------
all : $(Targ)
	$(Targ) cmds.txt

$(Targ) : $(Objs)
	gcc $(CCXFLAGS) -o $@ $(Objs)

$(Objs) : $(Srcs) $(Hdrs)

check :
	@ echo Srcs: $(Srcs)
	@ echo Hdrs: $(Hdrs)
	@ echo Objs: $(Objs)

# --------------------------------------------------------------------
neat :
	rm -f *~ *stackdump *.out *.o

clean : neat
	rm -f *exe
