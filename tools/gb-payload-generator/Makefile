SHELL := /bin/bash

ASM_DIR := src/payloads
OUTPUT_DIR := build
DEPENDENCIES_DIR := dependencies
OBJECT_FILE := $(OUTPUT_DIR)/$${file%%.*}.o
DATA_DIR := ../../data/

PAYLOADS := $(notdir $(wildcard $(ASM_DIR)/*.asm))
DEPENDENCY_FILES := $(notdir $(wildcard $(DEPENDENCIES_DIR)/*.asm))

.PHONY: all base language_specific clean

all: link

base: | $(OUTPUT_DIR)
	@set -e; \
	cd $(ASM_DIR); \
	for file in $(PAYLOADS); do \
		echo "Building base payload $$file"; \
		rgbasm -o ../../$(OBJECT_FILE) "./$$file"; \
		rgblink -x -o "../../$(OUTPUT_DIR)/$${file%%.*}.bin" ../../$(OBJECT_FILE); \
	done

language_specific: | $(OUTPUT_DIR)
	@set -e; \
	if [ -z "$(strip $(DEPENDENCY_FILES))" ]; then \
		echo "No dependency asm files found in $(DEPENDENCIES_DIR); skipping language-specific payloads."; \
		exit 0; \
	fi; \
	cd $(ASM_DIR); \
	for file in $(PAYLOADS); do \
		for dependency in $(DEPENDENCY_FILES); do \
			language_version="$${dependency%%.asm}"; \
			echo "Building $$file with $$language_version"; \
			rgbasm -P "../../$(DEPENDENCIES_DIR)/$$dependency" -o ../../$(OBJECT_FILE) "./$$file"; \
			rgblink -x -o "../../$(OUTPUT_DIR)/$${file%%.*}_$${language_version}.bin" ../../$(OBJECT_FILE); \
		done; \
	done

link: base language_specific
	@ls
	@cp $(OUTPUT_DIR)/*.bin $(DATA_DIR)

$(OUTPUT_DIR):
	@mkdir -p $(OUTPUT_DIR)

clean:
	@rm -rf $(OUTPUT_DIR)
