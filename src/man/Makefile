#Directory setup
CUR_DIR = $(shell pwd)
NBITES_DIR = $(CUR_DIR)/../..
BUILD_DIR = $(NBITES_DIR)/build/man
STRAIGHT_DIR = $(BUILD_DIR)/straight
CROSS_DIR = $(BUILD_DIR)/cross
WEBOTS_DIR = $(BUILD_DIR)/webots
CROSS_INSTALL_DIR = $(BUILD_DIR)/cross_install
WEBOTS_INSTALL_DIR = $(BUILD_DIR)/webots_install
CMAKE_DIR = cmake.man
CMAKE_STRAIGHT_DEPEND = $(STRAIGHT_DIR)/Makefile
CMAKE_WEBOTS_DEPEND = $(WEBOTS_DIR)/Makefile
CMAKE_CROSS_DEPEND = $(CROSS_DIR)/Makefile
#Source setup
CMAKE_SRCS = \
	CMakeLists.txt \
	buildconfig.cmake \
	manconfig.in
CMAKE_SRCS := $(addprefix $(CMAKE_DIR),$(CMAKE_SRCS))
#File setup
CONFIG_FILE = manconfig.h
INSTALL_SCRIPT = ./upload.sh
CROSS_FILE = $(BUILD_DIR)/cross_file
STRAIGHT_FILE = $(BUILD_DIR)/straight_file
WEBOTS_FILE = $(BUILD_DIR)/webots_file

PYC_FILES = $(shell find . -name "*.pyc")

CROSS_TOOLCHAIN = $(abspath $(CURDIR)/cmake/geode.cmake)
CMAKE_STRAIGHT_DEFS = -DOE_CROSS_BUILD=OFF -DSTRAIGHT=ON
CMAKE_CROSS_DEFS = -DCMAKE_TOOLCHAIN_FILE=$(CROSS_TOOLCHAIN) -DOE_CROSS_BUILD=ON
CMAKE_WEBOTS_DEFS = -DOE_CROSS_BUILD=OFF -DMAN_IS_REMOTE_=ON -DWEBOTS_BACKEND=ON -DCOLOR_TABLE=../../tables/uvy/webots/webots_6_2.mtb
CCMAKE_CROSS_OPT = -DCMAKE_SHARED_LINKER_FLAGS:STRING="" -DCMAKE_MODULE_LINKER_FLAGS:STRING=""
#Commands setup
CD=cd
RM=rm
CMAKE=cmake
CCMAKE=ccmake
MKDIR=mkdir
TOUCH=touch
MAKE_OPTIONS=--no-print-directory


.PHONY: default_target all straight cross cclean clean install noconfig
.PHONY: clean_install


default_target: all

all: $(CMAKE_STRAIGHT_DEPEND) $(CMAKE_WEBOTS_DEPEND) $(CMAKE_CROSS_DEPEND)
	@if [ -e $(CROSS_FILE) ]; then \
		$(MAKE) $(MAKE_OPTIONS) -C $(CROSS_DIR); \
	elif [ -e $(STRAIGHT_FILE) ]; then \
		$(MAKE) $(MAKE_OPTIONS) -C $(STRAIGHT_DIR); \
	elif [ -e $(WEBOTS_FILE) ]; then \
		$(MAKE) $(MAKE_OPTIONS) -C $(WEBOTS_DIR); \
	fi

$(CMAKE_WEBOTS_DEPEND):
	@if [ -f $(WEBOTS_FILE) ]; then \
		$(MAKE) $(MAKE_OPTIONS) webots; \
	fi

$(CMAKE_STRAIGHT_DEPEND):
	@if [ -f $(STRAIGHT_FILE) ]; then \
		$(MAKE) $(MAKE_OPTIONS) straight; \
	fi

$(CMAKE_CROSS_DEPEND):
	@if [ -f $(CROSS_FILE) ]; then \
		$(MAKE) $(MAKE_OPTIONS) cross; \
	fi


straight: $(STRAIGHT_FILE)
	@set -e;
		$(CD) $(STRAIGHT_DIR); \
		$(CCMAKE) .

$(STRAIGHT_FILE):
	@if [ -e $(CROSS_FILE) ]; then \
		$(RM) $(CROSS_FILE); \
	fi
	@if [ -e $(WEBOTS_FILE) ]; then \
		$(RM) $(WEBOTS_FILE); \
	fi
	@set -e; \
		$(MKDIR) -p $(BUILD_DIR); \
		$(TOUCH) $(STRAIGHT_FILE); \
		$(MKDIR) -p $(STRAIGHT_DIR); \
		$(CD) $(STRAIGHT_DIR); \
		$(CMAKE) $(CMAKE_STRAIGHT_DEFS) $(CURDIR)/$(CMAKE_DIR)

cross: $(CROSS_FILE)
	@set -e ; \
		$(CD) $(CROSS_DIR); \
		$(CCMAKE) $(CCMAKE_CROSS_OPT) .

$(CROSS_FILE):
	@if [ -e $(STRAIGHT_FILE) ]; then \
		$(RM) $(STRAIGHT_FILE); \
	fi
	@if [ -e $(WEBOTS_FILE) ]; then \
		$(RM) $(WEBOTS_FILE); \
	fi
	@set -e; \
		$(MKDIR) -p $(BUILD_DIR); \
		$(TOUCH) $(CROSS_FILE); \
		$(MKDIR) -p $(CROSS_DIR); \
		$(CD) $(CROSS_DIR); \
		$(CMAKE) $(CMAKE_CROSS_DEFS) $(CURDIR)/$(CMAKE_DIR)


webots: $(WEBOTS_FILE)
	@set -e;
		$(CD) $(WEBOTS_DIR); \
		$(CCMAKE) .

$(WEBOTS_FILE):
	@if [ -e $(STRAIGHT_FILE) ]; then \
		$(RM) $(STRAIGHT_FILE); \
	fi
	@if [ -e $(CROSS_FILE) ]; then \
		$(RM) $(CROSS_FILE); \
	fi
	@set -e; \
		$(MKDIR) -p $(BUILD_DIR); \
		$(TOUCH) $(WEBOTS_FILE); \
		$(MKDIR) -p $(WEBOTS_DIR); \
		$(CD) $(WEBOTS_DIR); \
		$(CMAKE) $(CMAKE_WEBOTS_DEFS) $(CURDIR)/$(CMAKE_DIR)


install: $(CMAKE_DEPEND)
	@if [ -e $(CROSS_FILE) ]; then \
		$(MAKE) $(MAKE_OPTIONS) -C $(CROSS_DIR) install; \
		$(INSTALL_SCRIPT); \
	elif [ -e $(WEBOTS_FILE) ]; then \
		$(MAKE) $(MAKE_OPTIONS) -C $(WEBOTS_DIR) install; \
		$(INSTALL_SCRIPT); \
	else \
		echo "Must have CROSS or WEBOTS build configured to 'make install'"; \
	fi


clean_install:
	$(RM) -r $(CROSS_INSTALL_DIR)/*
	$(RM) -r $(WEBOTS_INSTALL_DIR)/*

cclean: $(CMAKE_DEPEND)
	@$(MAKE) $(MAKE_OPTIONS) -C $(BUILD_DIR) clean

clean:
	$(RM) -r $(BUILD_DIR)

check:
	@if [ -e $(CROSS_FILE) ]; then \
		echo "Making for CROSS"; \
	elif [ -e $(STRAIGHT_FILE) ]; then \
		echo "Making for STRAIGHT"; \
	elif [ -e $(WEBOTS_FILE) ]; then \
		echo "Making for WEBOTS"; \
	fi
