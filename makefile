# Valid workstations are "OSX" and "UNIX"
WORKSTATION = UNIX


# COMPILED WITH:
#g++ GLFW_test.o -o main.exec -lglfw3 -lGLU -lGL -lX11 -lXxf86vm -lXrandr -lpthread -lXi  -lXrandr -lXcursor -lXfixes



#==== Common flags, settings and obj-files Settings ====#
# CXX 		is the active compiler
# TARGET	is the name of the executable file
# C_WFLAGS	contain common warning flags
# C_OBJS	contain common object-files. Object files should be named after the soruce
#		files but have .o - extention.

CXX = g++
TARGET = main.out
TESTTARGET = test.out
C_WFLAGS = -Wall
C_OBJS = ObjectManager_Test.o ObjectManager.o

# == System Specific flags == #
# Objs 		are to be named the same as the source-files except for .o - extention
# WFLAGS 	are warning-flag and compiler flags
# INCLUDEFLAGS 	are paths to headers
# LINKFLAGS 	are the actual source-packages that needs linking.

#==== UNIX Specific Settings ====#
ifeq ($(WORKSTATION),UNIX)
OBJS = $(C_OBJS)
WFLAGS = $(C_WFLAGS)
#INCLUDEFLAGS = `pkg-config --cflags gtk+-2.0`
#LINKFLAGS = -export-dynamic -lm -lXext -lX11 `pkg-config --libs gtk+-2.0` -lGL -lGLEW -lGLU -lglut
INCLUDEFLAGS =
LINKFLAGS = -export-dynamic -lglfw3 -lGLU -lGL -lX11 -lpthread -lXi -lXrandr -lXcursor -lXxf86vm 

endif

#==== OSX Specific Settings ====#
ifeq ($(WORKSTATION),OSX)
OBJS = $(C_OBJS)
WFLAGS = $(C_WFLAGS)
INCLUDEFLAGS = -I/opt/local/include 
LINKFLAGS = -L/opt/local/lib -framework OpenGL -framework cocoa -framework IOKit -lglfw3 -lGLEW
endif

#=== Execution ===#
# DEPS		is used to recompile *.o files whos header files have been edited
# OFLAGS 	is used for building Object files.
# TargetFLAGS 	is used for building target.

DEPS := $(OBJS:.o=.d)

OFLAGS = $(INCLUDEFLAGS) $(WFLAGS)
TARGETFLAGS = $(LINKFLAGS)

# Buld Target
all: $(TARGET)
# Remove Target, *.o and *.d files
clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)

# Clean up and rebuild from scratch
rebuild: clean all

# Build target
$(TARGET):  $(OBJS)	
	$(CXX) $(OBJS) -o $(TARGET) $(TARGETFLAGS)

# Build object files
%.o: %.cpp
	$(CXX) -MMD -MP -D$(WORKSTATION) $(OFLAGS) -c $<

# Include dependencies
-include $(DEPS)

