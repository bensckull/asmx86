#  -----------------------------------------------------------------------------
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 3 of the License.
#  -----------------------------------------------------------------------------

#  -----------------------------------------------------------------------------
#    Custom variables
#  -----------------------------------------------------------------------------

NAME    = asmx86
FILES   = *.cpp

#  -----------------------------------------------------------------------------
#    Flags
#  -----------------------------------------------------------------------------

CPPFLAGS += -std=c++14

#  -----------------------------------------------------------------------------
#    Options
#  -----------------------------------------------------------------------------

# Optimize code with -O2
OPTIMIZE?=yes

ifeq ($(OPTIMIZE),yes)
CPPFLAGS += -O2
endif

# Set warning flags
WARNING?=yes

ifeq ($(WARNING),yes)
CPPFLAGS += -Wall
endif

# Set error flags
ERROR?=yes

ifeq ($(ERROR),yes)
CPPFLAGS += -Werror
endif

#  -----------------------------------------------------------------------------
#    Define
#  -----------------------------------------------------------------------------

define colorecho
    @tput bold
    @tput setaf 3
    @echo $1
    @tput sgr0
endef

#  -----------------------------------------------------------------------------
#    Make
#  -----------------------------------------------------------------------------

all: checkdirs link

link:
	$(call colorecho,"Linking" $(NAME))
	g++ $(CPPFLAGS) $(FILES) -o $(NAME) -I.
	@echo

doxygen:
	$(call colorecho,"Generate" $(NAME) "doc")
	doxygen asmx86doc

checkdirs: $(BUILD_DIR)
	$(call colorecho,"Check variables")
	@echo \
	  " OPTIMIZE : $(OPTIMIZE)\n" \
	  "WARNING  : $(WARNING)\n" \
	  "FLAGS    : $(CPPFLAGS)\n" \

clean:
	rm -f $(NAME)
