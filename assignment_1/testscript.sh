echo
echo
echo

echo "Running 'make'"
make


echo 
echo "1: Testing pgmEcho for invalid inputs"
./pgmEcho images/fakeTest images/fakeTest.pgm
echo -e "\n1 Result: Returned $?"
echo

echo "2: Testing pgmEcho for valid inputs"
./pgmEcho images/slice0a.pgm images/realTest.pgm
echo -e "\n2 Result: Returned $?"
rm images/realTest.pgm
echo

echo "3: Testing pgmComp for valid inputs"
./pgmComp images/slice0a.pgm images/slice0a.pgm
echo -e "\n3 Result: Returned $?"
echo

echo "4: Testing pgma2b"
./pgma2b images/slice0a.pgm images/slice0b.pgm
echo
./pgmComp images/slice0a.pgm images/slice0b.pgm
echo -e "\n4 Result: Returned $?"
echo

echo "5: Testing pgmb2a"
./pgmb2a images/slice0b.pgm images/newSlice0a.pgm
echo -e 
./pgmComp images/slice0b.pgm images/newSlice0a.pgm
echo -e "\n5 Result: Returned $?"
echo

echo "6: Testing pgmComp for non-equivalent pgms"
./pgmComp images/slice0a.pgm images/notSlice0a.pgm
echo -e "\n6 Result: Returned $?"
echo

echo "7: Testing pgmComp for non-equivalent pgms"
./pgmComp images/slice0a.pgm images/slice0b.pgm
echo -e "\n7 Result: Returned $?"
echo

echo "8: Testing pgmReduce for reduction factor 4"
./pgmReduce images/baboon.ascii.pgm 4 images/reducedBaboon.ascii.pgm
echo -e "\n8 Result: Returned $?"
rm images/reducedBaboon.ascii.pgm
echo

echo "9: Testing pgmTile for tile factor 4"
./pgmTile images/baboon.ascii.pgm 4 "images/tiledBaboon.ascii.pgm_<row>_<column>.pgm"
echo -e "\n9 Result: Returned $?"
rm images/tiledBaboon.*
echo

echo "Running 'make clean'"
make clean
