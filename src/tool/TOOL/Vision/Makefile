PLATFORM := $(shell uname)
META_DIR := ../..
NBITES_DIR := $(META_DIR)/../..
BUILD_DIR := $(NBITES_DIR)/build/tool
DIR := TOOL/Vision
TEST_CLASS := None

JP = /System/Library/Frameworks/JavaVM.framework/Versions/1.5

ifeq  "$(PLATFORM)" "Darwin"
JCP = $(JP)/Commands
JHP = $(JP)/Headers
JAVA = $(JCP)/java
JAVAC = $(JCP)/javac
JAVAH = $(JCP)/javah
else
JAVA = java
JAVAC = javac
JAVAH = javah
endif

ifeq "$(PLATFORM)" "CYGWIN_NT-5.1"
JAVA_OPTS = -classpath "../../."
else
JAVA_OPTS = -classpath "../../." 
endif

JAR = $(JCP)/jar 

TOOL_CLASS_PATH := TOOL

#For compiling JNI vision library
MAN_HOME := $(META_DIR)/../man

NATIVE_VISION_SRCS := TOOLVisionLink.cpp
NATIVE_VISION_LIBS := $(MAN_HOME)/build/cmake.vision/libvision.a \
	$(MAN_HOME)/build/cmake.man.corpus/libsensors.a \
$(MAN_HOME)/build/cmake.man.corpus/libnbinclude.a


NATIVE_VISION_CLASS_FILE := TOOLVisionLink
NATIVE_VISION_JAVA_CLASS_NAME :=  $(TOOL_CLASS_PATH).Vision.$(NATIVE_VISION_CLASS_FILE)
NATIVE_VISION_HEADER_FILE := $(subst .,_,$(TOOL_CLASS_PATH))_Vision_$(NATIVE_VISION_CLASS_FILE)


COMPILE_TIME_DEFS := -DNO_ZLIB -DROBOT_TYPE=NAO_RL

ifeq  "$(PLATFORM)" "Darwin"
JAVA_INCLUDE:=-I$(JHP)
FINK_INCLUDE := -I/sw/include
NATIVE_VISION_TARGET := $(META_DIR)/lib$(NATIVE_VISION_CLASS_FILE).jnilib
VISION_SHARED_OPTS := -dynamiclib -m32
else

JAVA_INCLUDE:= -I/usr/lib/jvm/java-1.5.0-sun/include/linux/ -I/usr/lib/jvm/java-1.5.0-sun/include/ -I/usr/lib/jvm/java-6-sun/include/ -I/usr/lib/jvm/java-6-sun/include/linux/

VISION_SHARED_OPTS := -shared -fpic
NATIVE_VISION_TARGET := $(META_DIR)/lib$(NATIVE_VISION_CLASS_FILE).so
endif
PYTHON_INCLUDE:= -I/usr/include/python2.5/
PYLIBS := -lpython2.5

NBITES_INCLUDE :=-I$(MAN_HOME)/vision -I$(MAN_HOME)/include -I$(MAN_HOME)/corpus -I$(MAN_HOME)/motion -I$(MAN_HOME)/noggin -I$(MAN_HOME)/
VISION_INCLUDE := $(JAVA_INCLUDE) $(NBITES_INCLUDE) $(PYTHON_INCLUDE)  $(FINK_INCLUDE)


.PHONY: all clean run

all:
	$(MAKE) -C $(META_DIR) vision

clean: clean_vision
	$(RM) *.class


run:
	$(MAKE) -C $(META_DIR) run

test:	all
	cd $(META_DIR) && $(JAVA) $(DIR)/$(TEST_CLASS)

%.class: %.java
	$(MAKE) -C $(META_DIR) $(DIR)/$@

clean_vision:
	$(RM) $(NATIVE_VISION_TARGET) 	$(NATIVE_VISION_HEADER_FILE).h

vision: $(NATIVE_VISION_TARGET)

$(NATIVE_VISION_TARGET) : $(NATIVE_VISION_LIBS) $(NATIVE_VISION_SRCS)
	@echo $(NATIVE_VISION_TARGET)
	$(JAVAC) $(JAVA_OPTS) $(NATIVE_VISION_CLASS_FILE).java Ball.java VisualCorner.java VisualFieldObject.java LinePoint.java VisualLine.java Horizon.java
	$(JAVAH) -jni -classpath $(BUILD_DIR) $(NATIVE_VISION_JAVA_CLASS_NAME)
	$(CXX) -o $(NATIVE_VISION_TARGET) $(NATIVE_VISION_SRCS) $(NATIVE_VISION_LIBS)  $(VISION_SHARED_OPTS) $(VISION_INCLUDE) $(PYLIBS) $(COMPILE_TIME_DEFS)  
