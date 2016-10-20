.PHONY: all update doc

export PATH:=$(PWD)/tools/bin:$(PATH)

modules_export:
	@echo "Exporting modules..."
	@for d in modules/* ; do (cd $$d ; conan export AversivePlusPlus/dev) ; done
	@for d in toolchains/* ; do (cd $$d ; conan export AversivePlusPlus/dev) ; done
	conan export AversivePlusPlus/dev

update:
	git submodule update --init

doc:
	@mkdir build -p
	doxygen
