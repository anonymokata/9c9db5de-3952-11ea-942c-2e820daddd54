output: test_main.o test_product.o product.o test_register.o register.o
	g++ -std=c++11 -Wall -Werror test_main.o test_product.o product.o test_register.o register.o -o output

test_main.o: test/test_main.cpp
	g++ -std=c++11 -Wall -Werror -c test/test_main.cpp -I lib/catch2

test_product.o: test/test_product.cpp
	g++ -std=c++11 -Wall -Werror -c test/test_product.cpp -I lib/catch2 -I src/

product.o: src/product.cpp
	g++ -std=c++11 -Wall -Werror -c src/product.cpp -I src/

test_register.o: test/test_register.cpp
	g++ -std=c++11 -Wall -Werror -c test/test_register.cpp -I lib/catch2 -I src/

register.o: src/register.cpp
	g++ -std=c++11 -Wall -Werror -c src/register.cpp -I src/

clean:
	rm *.o output

test: output
	./output
