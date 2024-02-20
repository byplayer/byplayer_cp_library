.PHONY : clean
clean:
	$(RM) -r docs

doc:
	doxygen Doxyfile
