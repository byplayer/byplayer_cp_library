.PHONY: clean doc test
clean:
	$(RM) -r docs
	cd test/unittest && make clean

doc:
	doxygen Doxyfile

test:
	cd test/unittest && make test

.DEFAULT_GOAL = test
