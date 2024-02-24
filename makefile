.PHONY: clean doc test
clean:
	$(RM) -r docs

doc:
	doxygen Doxyfile

test:
	cd test/unittest && make test

.DEFAULT_GOAL = test
