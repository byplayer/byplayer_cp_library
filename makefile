.PHONY: clean doc
clean:
	$(RM) -r docs

doc:
	doxygen Doxyfile

.DEFAULT_GOAL = doc
