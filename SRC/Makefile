TOO=g++ -std=gnu++11 -fpic -c
TOSO=g++ -shared -o 
TOOUT=g++ -std=gnu++11
BUILD_DIR = $(realpath $(CURDIR))/../build
SOURCE_DIR= $(realpath $(CURDIR))


string_operator: string_operator.cpp
				$(TOO) string_operator.cpp
				$(TOSO) libstring_operator.so string_operator.o
				@cd .. ; mkdir build 
				@mv ./string_operator.o $(BUILD_DIR)
				@mv ./libstring_operator.so $(BUILD_DIR)

gmFoamTranslator: gmFoamTranslator.cpp
				$(TOO) gmFoamTranslator.cpp
				$(TOSO) libgmFoamTranslator.so gmFoamTranslator.o
				@mv ./gmFoamTranslator.o $(BUILD_DIR)
				@mv ./libgmFoamTranslator.so $(BUILD_DIR)
try: string_operator gmFoamTranslator mesh_conversion
	$(TOOUT) try.cpp -o try -L$(BUILD_DIR)  -lgmFoamTranslator -lstring_operator -Wl,-rpath=$(BUILD_DIR)
	@mv ./try $(BUILD_DIR)
	@sudo ln -sf $(BUILD_DIR)/try /usr/local/bin 

clean: 
	@cd $(BUILD_DIR); rm -r $(BUILD_DIR)
rebuild: clean try

mesh_conversion: $(SOURCE_DIR)/gmsh_conversion_reserved
	@if [ -f "./gmsh_conversion" ]; then rm ./gmsh_conversion; fi
	@cp ./gmsh_conversion_reserved ./gmsh_conversion
	@echo export SOURCE_DIR=$(PWD)| cat - gmsh_conversion > temp && mv temp gmsh_conversion
	@echo '#!/bin/bash' | cat - gmsh_conversion > temp && mv temp gmsh_conversion
	@sudo ln -sf $(SOURCE_DIR)/gmsh_conversion /usr/local/bin
	@cd /usr/local/bin ; sudo chmod +x gmsh_conversion

# demo: clean string_operator
# 	$(TOOUT) demo.cpp -o demo -L$(BUILD_DIR) -lstring_operator -Wl,-rpath=$(BUILD_DIR)