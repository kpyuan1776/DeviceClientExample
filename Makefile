install:
	@sudo apt-get install gcovr lcov

install_doc:
	@pip install jinja2 Pygments
	@sudo apt-get install doxygen

install_lib:
	@sudo apt install libopenblas-dev liblapack-dev

setup:
	@pip install jinja2 Pygments
	@sudo apt-get install doxygen	

prepare:
	@rm -rf build
	@mkdir build
	@cd build && conan install .. && cd ..