CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

adventurer:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtestadventurer.c rngs.c -o randomtestadventurer -lm -g

runAdventurer: adventurer
	./randomtestadventurer &> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

randomcard:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtestcard.c rngs.c -o randomtestcard -lm -g

runRandomCard: randomcard
	./randomtestcard &> randomtestcard.out
	gcov dominion.c >> randomtestcard.out
	cat dominion.c.gcov >> randomcard.out


playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

playdom2: dominion.o playdom2.c
	gcc -o playdom2 playdom2.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

unit1:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest1.c rngs.c -o unittest1 -lm -g

unit2:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest2.c rngs.c -o unittest2 -lm -g

unit3:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest3.c rngs.c -o unittest3 -lm -g

unit4:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest4.c rngs.c -o unittest4 -lm -g

card1:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest1.c rngs.c -o cardtest1 -lm -g

card2:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest2.c rngs.c -o cardtest2 -lm -g

card3:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest3.c rngs.c -o cardtest3 -lm -g

card4:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest4.c rngs.c -o cardtest4 -lm -g


myTest:
	./unittest1 &> unittestresult.out
	./unittest2 >> unittestresult.out
	./unittest3 >> unittestresult.out
	./unittest4 >> unittestresult.out
	./cardtest1 >> unittestresult.out
	./cardtest2 >> unittestresult.out
	./cardtest3 >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

# =======================================================================
# Makiah Merritt, CS 362 Assignment 2
# Unit Tests
merrittm_unittest1: ./assign2/unittest1.c dominion.o rngs.o
	gcc -o merrittm_unittest1 -g  ./assign2/unittest1.c dominion.o rngs.o $(CFLAGS)

merrittm_unittest2: ./assign2/unittest2.c dominion.o rngs.o
	gcc -o merrittm_unittest2 -g  ./assign2/unittest2.c dominion.o rngs.o $(CFLAGS)

merrittm_unittest3: ./assign2/unittest3.c dominion.o rngs.o
	gcc -o merrittm_unittest3 -g  ./assign2/unittest3.c dominion.o rngs.o $(CFLAGS)

merrittm_unittest4: ./assign2/unittest4.c dominion.o rngs.o
	gcc -o merrittm_unittest4 -g  ./assign2/unittest4.c dominion.o rngs.o $(CFLAGS)

# Card Tests
merrittm_cardtest1: ./assign2/cardtest1.c dominion.o rngs.o
	gcc -o merrittm_cardtest1 -g  ./assign2/cardtest1.c dominion.o rngs.o $(CFLAGS)

merrittm_cardtest2: ./assign2/cardtest2.c dominion.o rngs.o
	gcc -o merrittm_cardtest2 -g  ./assign2/cardtest2.c dominion.o rngs.o $(CFLAGS)

merrittm_cardtest3: ./assign2/cardtest3.c dominion.o rngs.o
	gcc -o merrittm_cardtest3 -g  ./assign2/cardtest3.c dominion.o rngs.o $(CFLAGS)

merrittm_cardtest4: ./assign2/cardtest4.c dominion.o rngs.o
	gcc -o merrittm_cardtest4 -g  ./assign2/cardtest4.c dominion.o rngs.o $(CFLAGS)


# Make and run all tests:
assign2: merrittm_unittest1 merrittm_unittest2 merrittm_unittest3 merrittm_unittest4 merrittm_cardtest1 merrittm_cardtest2 merrittm_cardtest3 merrittm_cardtest4
	rm -f ./assign2/merrittm_unittestresult.txt
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" >> ./assign2/merrittm_unittestresult.txt
	echo -n "Unit Testing - Assign 2 - Run: " >> ./assign2/merrittm_unittestresult.txt
	date >> ./assign2/merrittm_unittestresult.txt
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" >> ./assign2/merrittm_unittestresult.txt

	merrittm_unittest1
	echo "=================================================" >> ./assign2/merrittm_unittestresult.txt
	echo "merrittm_unittest1" >> ./assign2/merrittm_unittestresult.txt
	gcov ./dominion.c >> ./assign2/merrittm_unittestresult.txt
	echo "=================================================" >> ./assign2/merrittm_unittestresult.txt
	cat dominion.c.gcov >> ./assign2/merrittm_unittestresult.txt
	echo >> ./assign2/merrittm_unittestresult.txt

	merrittm_unittest2
	echo "=================================================" >> ./assign2/merrittm_unittestresult.txt
	echo "merrittm_unittest2" >> ./assign2/merrittm_unittestresult.txt
	gcov ./dominion.c >> ./assign2/merrittm_unittestresult.txt
	echo "=================================================" >> ./assign2/merrittm_unittestresult.txt
	cat dominion.c.gcov >> ./assign2/merrittm_unittestresult.txt
	echo >> ./assign2/merrittm_unittestresult.txt


	merrittm_unittest3
	echo "=================================================" >> ./assign2/merrittm_unittestresult.txt
	echo "merrittm_unittest3" >> ./assign2/merrittm_unittestresult.txt
	gcov ./dominion.c >> ./assign2/merrittm_unittestresult.txt
	echo "=================================================" >> ./assign2/merrittm_unittestresult.txt
	cat dominion.c.gcov >> ./assign2/merrittm_unittestresult.txt
	echo >> ./assign2/merrittm_unittestresult.txt


	merrittm_unittest4
	echo "=================================================" >> ./assign2/merrittm_unittestresult.txt
	echo "merrittm_unittest4" >> ./assign2/merrittm_unittestresult.txt
	gcov ./dominion.c >> ./assign2/merrittm_unittestresult.txt
	echo "=================================================" >> ./assign2/merrittm_unittestresult.txt
	cat dominion.c.gcov >> ./assign2/merrittm_unittestresult.txt
	echo >> ./assign2/merrittm_unittestresult.txt


	merrittm_cardtest1
	echo "=================================================" >> ./assign2/merrittm_unittestresult.txt
	echo "merrittm_cardtest1" >> ./assign2/merrittm_unittestresult.txt
	gcov ./dominion.c >> ./assign2/merrittm_unittestresult.txt
	echo "=================================================" >> ./assign2/merrittm_unittestresult.txt
	cat dominion.c.gcov >> ./assign2/merrittm_unittestresult.txt
	echo >> ./assign2/merrittm_unittestresult.txt


	merrittm_cardtest2
	echo "=================================================" >> ./assign2/merrittm_unittestresult.txt
	echo "merrittm_cardtest2" >> ./assign2/merrittm_unittestresult.txt
	gcov ./dominion.c >> ./assign2/merrittm_unittestresult.txt
	echo "=================================================" >> ./assign2/merrittm_unittestresult.txt
	cat dominion.c.gcov >> ./assign2/merrittm_unittestresult.txt
	echo >> ./assign2/merrittm_unittestresult.txt


	merrittm_cardtest3
	echo "=================================================" >> ./assign2/merrittm_unittestresult.txt
	echo "merrittm_cardtest3" >> ./assign2/merrittm_unittestresult.txt
	gcov ./dominion.c >> ./assign2/merrittm_unittestresult.txt
	echo "=================================================" >> ./assign2/merrittm_unittestresult.txt
	cat dominion.c.gcov >> ./assign2/merrittm_unittestresult.txt
	echo >> ./assign2/merrittm_unittestresult.txt


	merrittm_cardtest4
	echo "=================================================" >> ./assign2/merrittm_unittestresult.txt
	echo "merrittm_cardtest4" >> ./assign2/merrittm_unittestresult.txt
	gcov ./dominion.c >> ./assign2/merrittm_unittestresult.txt
	echo "=================================================" >> ./assign2/merrittm_unittestresult.txt
	cat dominion.c.gcov >> ./assign2/merrittm_unittestresult.txt
	echo >> ./assign2/merrittm_unittestresult.txt


# =======================================================================
# Makiah Merritt, CS 362 Assignment 3
# Random Tests
merrittm_randtest1: ./randomtestadventurer.c dominion.o rngs.o
	gcc -o merrittm_randomtest1 -g  ./randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

merrittm_randtest2: ./assign3/randomtest_remodel.c dominion.o rngs.o
	gcc -o merrittm_randomtest2 -g  ./assign3/randomtest_remodel.c dominion.o rngs.o $(CFLAGS)

assign3: merrittm_randtest1 merrittm_randtest2


# =======================================================================
# Makiah Merritt, CS 362 Assignment 4
# Random Test Dominion
merrittm_randtestdominion: ./assign4/testdominion.c ./dominion.o ./rngs.o
	gcc -o merrittm_randtestdominion -g ./assign4/testdominion.c ./dominion.o ./rngs.o $(CFLAGS)

assign4: merrittm_randtestdominion

run_assign4: merrittm_randtestdominion
	rm -f -v gameResults.out
	#ulimit -t 10;	# limit CPU time in bash
	#limit -t 10;	# limit CPU time in tsch
	merrittm_randtestdominion | tee gameResults.out

# =======================================================================

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	clear
	# Removing Files
	rm -f -v *.o playdom.exe playdom test.exe test player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so merrittm_unittest1 merrittm_unittest2 merrittm_unittest3 merrittm_unittest4 merrittm_cardtest1 merrittm_cardtest2 merrittm_cardtest3 merrittm_cardtest4 merrittm_randomtest1 merrittm_randomtest2 merrittm_randtestdominion
