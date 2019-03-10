build:
	g++ main.cpp -o ex;
run1:
	./ex < a_example.txt;
run3:
	./ex < c_memorable_moments.txt;
clean:
	rm -rf ex;
archive:
	zip cod.zip *