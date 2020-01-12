output: test_main.o test_use_cases.o test_product.o product.o test_register.o register.o test_inventory.o inventory.o test_special.o special.o
	g++ -std=c++11 -Wall -Werror test_main.o test_use_cases.o test_product.o product.o test_register.o register.o test_inventory.o inventory.o test_special.o special.o -o output

test_main.o: test/test_main.cpp
	g++ -std=c++11 -Wall -Werror -c test/test_main.cpp -I lib/catch2

test_use_cases.o: test/test_use_cases.cpp
	g++ -std=c++11 -Wall -Werror -c test/test_use_cases.cpp -I lib/catch2 -I src/

test_product.o: test/test_product.cpp
	g++ -std=c++11 -Wall -Werror -c test/test_product.cpp -I lib/catch2 -I src/

product.o: src/product.cpp
	g++ -std=c++11 -Wall -Werror -c src/product.cpp -I src/

test_register.o: test/test_register.cpp
	g++ -std=c++11 -Wall -Werror -c test/test_register.cpp -I lib/catch2 -I src/

register.o: src/register.cpp
	g++ -std=c++11 -Wall -Werror -c src/register.cpp -I src/

test_inventory.o: test/test_inventory.cpp
	g++ -std=c++11 -Wall -Werror -c test/test_inventory.cpp -I lib/catch2 -I src/

inventory.o: src/inventory.cpp
	g++ -std=c++11 -Wall -Werror -c src/inventory.cpp -I src/

test_special.o: test/test_special.cpp
	g++ -std=c++11 -Wall -Werror -c test/test_special.cpp -I lib/catch2 -I src/

special.o: src/special.cpp
	g++ -std=c++11 -Wall -Werror -c src/special.cpp -I src/

clean:
	rm *.o output

test: output
	./output
