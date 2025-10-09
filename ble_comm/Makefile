
APP      := ble_comm
SRC      := src/main.c
BUILD    := build
ARCH     ?= x86_64
CC       :=
CFLAGS   := -O2 -Wall
LDFLAGS  := $(shell pkg-config --libs bluez)
CINCLUDES := $(shell pkg-config --cflags bluez)

# What are we compiling for?
ifeq ($(ARCH),arm32)
    CROSS_COMPILE := arm-linux-gnueabihf-
endif
ifeq ($(ARCH),arm64)
    CROSS_COMPILE := aarch64-linux-gnu-
endif
ifeq ($(ARCH),x86_64)
    CROSS_COMPILE :=
endif

CC := $(CROSS_COMPILE)gcc

OUT := $(BUILD)/$(APP)-$(ARCH)

all: $(OUT)

$(OUT): $(SRC)
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) $(CINCLUDES) $(SRC) -o $(OUT) $(LDFLAGS)
	@echo "Built $@"

clean:
	rm -rf $(BUILD)
