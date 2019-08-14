# Copyright 2019 Cartesi Pte. Ltd.
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License. You may obtain a copy of
# the License at http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations under
# the License.
#

UNAME:=$(shell uname)

EMULATOR_INC =
EMULATOR_DEP =

DEPDIR := third-party
SRCDIR := $(abspath src)
BUILDDIR = $(abspath build)
DOWNLOADDIR := $(DEPDIR)/downloads
SRCCLEAN := $(addsuffix .clean,$(SRCDIR))
DEPDIRS := $(addprefix $(DEPDIR)/,dtc-1.4.7)
DEPCLEAN := $(addsuffix .clean,$(DEPDIRS))

TOOLCHAIN_TAG ?= devel

ifeq ($(EMULATOR_INC),)
EMULATOR_DEP = $(DEPDIR)/machine-emulator
EMULATOR_INC = $(abspath $(EMULATOR_DEP)/src)
endif

RVCC  = riscv64-unknown-linux-gnu-gcc
RVCXX = riscv64-unknown-linux-gnu-g++
RVCOPY = riscv64-unknown-linux-gnu-objcopy
RVDUMP = riscv64-unknown-linux-gnu-objdump

all: $(SRCDIR)

clean: $(SRCCLEAN)

depclean: $(DEPCLEAN) clean
	rm -rf $(BUILDDIR)

distclean: clean
	rm -rf $(BUILDDIR) $(DOWNLOADDIR) $(DEPDIRS) $(EMULATOR_DEP)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)/lib

$(DEPDIR)/machine-emulator:
	if [ ! -d $@ ]; then git clone --branch master --depth 1 git@github.com:cartesi/machine-emulator.git $@; fi

$(DEPDIR)/dtc-1.4.7:
	tar -xzf $(DOWNLOADDIR)/v1.4.7.tar.gz -C $(DEPDIR)
	cd $@ && patch -p0 < ../dtc_build.patch
	$(MAKE) -C $@ CC=$(RVCC) libfdt/libfdt.a
	$(MAKE) -C $@ PREFIX=$(BUILDDIR) install-includes
	cp $@/libfdt/libfdt.a $(BUILDDIR)/lib

downloads: $(EMULATOR_DEP)
	mkdir -p $(DOWNLOADDIR)
	wget -nc -i $(DEPDIR)/dependencies -P $(DOWNLOADDIR)
	cd $(DEPDIR) && shasum -c shasumfile

dep: $(BUILDDIR) $(DEPDIRS)

$(SRCDIR):
	$(MAKE) -C $@ CC=$(RVCC) CXX=$(RVCXX) OBJCOPY=$(RVCOPY) OBJDUMP=$(RVDUMP) EMULATOR_INC=$(EMULATOR_INC) $(TARGET)

$(SRCCLEAN) $(DEPCLEAN): %.clean:
	$(MAKE) -C $* clean

toolchain-env:
	@docker run --hostname toolchain-env -it --rm \
		-e USER=$$(id -u -n) \
		-e GROUP=$$(id -g -n) \
		-e UID=$$(id -u) \
		-e GID=$$(id -g) \
		-v `pwd`:/opt/cartesi/machine-emulator-rom \
		-w /opt/cartesi/machine-emulator-rom \
		cartesi/image-toolchain:$(TOOLCHAIN_TAG)

.PHONY: all clean distclean downloads $(SRCDIR) $(DEPDIRS) $(SRCCLEAN) $(DEPCLEAN)
