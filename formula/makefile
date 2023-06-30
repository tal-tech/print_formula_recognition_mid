
OPENCV_INCLUDE=./include

LIBDIR = -Wl,--start-group -L./lib  -lm -lstdc++ -lrt -lrec_formula_recognization  -lopencv_imgproc -lopencv_imgcodecs -lopencv_core -lmerge_process -Wl,--end-group\
          -Wl,-rpath,./lib
CPPFLAGS = -Wall -Winline -pipe -ffast-math -D_LINUX_64_  -mavx -mavx2 -msse -fpermissive  
INCLUDEDIR = -I./include -I$(OPENCV_INCLUDE)
			  
define mkObjDir
    @ test -d $(1) || mkdir -p $(1)
endef

define mkGitInfo
	@echo `git log | head -3` > output/version.txt
	@echo "------" >> output/version.txt
	@echo `git diff` >> output/version.txt
endef

GCC := g++ -std=gnu++11 -w -fopenmp

OBJDIR := obj

TARGET1 := test_det
TARGET2 := test_det_deubg


#COREOBJ := ./src/merge_model/merge_model.o 
COREOBJ := ./src/json/json.o \
	./demo.o \
	  
			
COREOBJ_DEBUG = $(patsubst %.o,%_debug.o,$(COREOBJ))

OBJ1 = $(addprefix $(OBJDIR)/, $(COREOBJ))
OBJ2 = $(addprefix $(OBJDIR)/, $(COREOBJ_DEBUG))


all: $(TARGET1) $(TARGET2)
	

$(TARGET1) : $(OBJ1) 
	$(GCC)  -o $@ $^ $(LIBDIR) $(INCLUDEDIR) 
$(TARGET2) : $(OBJ2) 
	$(GCC)   -g -o $@ $^ $(LIBDIR) $(INCLUDEDIR)


$(OBJDIR)/%.o : %.cpp
	@ test -d $(OBJDIR) || mkdir -p $(OBJDIR)
	$(call mkObjDir,$(dir $@))
	$(GCC) -O2 $(CPPFLAGS) -c $< -o $@ $(INCLUDEDIR)

$(OBJDIR)/%_debug.o : %.cpp
	@ test -d $(OBJDIR) || mkdir -p $(OBJDIR)
	$(call mkObjDir,$(dir $@))
	$(GCC) $(CPPFLAGS) -g -c $< -o $@ $(INCLUDEDIR)

clean:
	rm -rf ./obj
	rm -rf $(TARGET1)
	rm -rf $(TARGET2)

