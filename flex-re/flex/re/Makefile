all: oh-one-one no-ab calculator no-abc no-zero-one-one even

no-abc: no-abc.ll
		flex -o no-abc.cc no-abc.ll
		g++ -std=c++17 -g -o no-abc no-abc.cc
oh-one-one: oh-one-one.ll
	flex -o oh-one-one.cc oh-one-one.ll
	g++ -std=c++17 -g -o oh-one-one oh-one-one.cc

no-ab: no-ab.ll
	flex -o no-ab.cc no-ab.ll
	g++ -std=c++17 -g -o no-ab no-ab.cc

calculator: calculator.ll
	flex -o calculator.cc calculator.ll
	g++ -std=c++17 -g -o calculator calculator.cc

no-zero-one-one: no-zero-one-one.ll
	flex -o no-zero-one-one.cc no-zero-one-one.ll
	g++ -std=c++17 -g -o no-zero-one-one no-zero-one-one.cc

even: even.ll
	flex -o even.cc even.ll
	g++ -std=c++17 -g -o even even.cc


clean:
	touch oh-one-one no-ab calculator no-abc no-zero-one-one even foo~
	rm *~ oh-one-one no-ab calculator no-abc no-zero-one-one even
	touch oh-one-one.cc no-ab.cc no-abc.cc calculator.cc no-zero-one-one.cc even.cc
	rm  oh-one-one.cc no-ab.cc no-abc.cc no-zero-one-one.cc calculator.cc even.cc
