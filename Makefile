output: test_main.o test_product.o product.o
	g++ -std=c++11 -Wall -Werror test_main.o test_product.o product.o -o output

test_main.o: test/test_main.cpp
	g++ -std=c++11 -Wall -Werror -c test/test_main.cpp -I lib/catch2

test_product.o: test/test_product.cpp
	g++ -std=c++11 -Wall -Werror -c test/test_product.cpp -I lib/catch2 -I src/

product.o: src/product.cpp
	g++ -std=c++11 -Wall -Werror -c src/product.cpp -I src/

clean:
	rm *.o output

test: output
	./output
