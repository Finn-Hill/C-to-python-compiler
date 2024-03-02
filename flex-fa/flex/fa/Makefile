all: oh-one-one balanced zooe abs ezo bf

oh-one-one: oh-one-one.ll FALexer.hh
	flex -o oh-one-one.cc oh-one-one.ll
	g++ -std=c++17 -g -o oh-one-one oh-one-one.cc

balanced: balanced.ll balanced.hh
	flex -o balanced.cc balanced.ll
	g++ -std=c++17 -g -o balanced balanced.cc

zooe: zooe.ll FALexer.hh
	flex -o zooe.cc zooe.ll
	g++ -std=c++17 -g -o zooe zooe.cc

abs: abs.ll FALexer.hh
	flex -o abs.cc abs.ll
	g++ -std=c++17 -g -o abs abs.cc

ezo: ezo.ll FALexer.hh
	flex -o ezo.cc ezo.ll
	g++ -std=c++17 -g -o ezo ezo.cc

bf: bf.ll FALexer.hh
	flex -o bf.cc bf.ll
	g++ -std=c++17 -g -o bf bf.cc


clean:
	touch oh-one-one balanced zooe abs ezo bf foo~
	rm *~ oh-one-one balanced zooe abs ezo bf
	touch oh-one-one.cc balanced.cc zooe.cc abs.cc ezo.cc bf.cc
	rm oh-one-one.cc balanced.cc zooe.cc abs.cc ezo.cc bf.cc
