.PHONY: all update doc

modules_conan_export:
	git submodule foreach conan export AversivePlusPlus/dev

update:
	./script/update.sh

doc:
	@mkdir build -p
	doxygen
