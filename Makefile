#Name: Kevin Sanchez
#Email: kxs152130@utdallas.edu
#Class: CS 3377.002
#Homework #6
#
#
CXX = g++
CXXFLAGS =
CPPFLAGS = -Wall -g -I/people/cs/s/sxp127930/include
LDFLAGS = -L/people/cs/s/sxp127930/lib
LDLIBS = -lcdk -lcurses 
#
#
# #
# # PROJECTNAME is a descriptive name used for the backup target
# # This should not contain spaces or special characters
#
EXECFILE = cdkexample
#
OBJS = example1.o
#
#
all: $(EXECFILE)
#
clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ \#*
#
#
$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)
#
backup:
	@make clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename "`pwd`"))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME) 2> /dev/null
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!
											# 			
