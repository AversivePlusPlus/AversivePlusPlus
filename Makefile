.PHONY: all update doc

modules_export:
	@for d in modules/* ; do (cd $$d ; $(PWD)/tools/bin/conan export AversivePlusPlus/dev) ; done
	@for d in toolchain/* ; do (cd $$d ; $(PWD)/tools/bin/conan export AversivePlusPlus/dev) ; done
	$(PWD)/tools/bin/conan export AversivePlusPlus/dev

update:
	./script/update.sh

doc:
	@mkdir build -p
	doxygen
