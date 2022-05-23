echo
echo
echo

echo "Running 'make'"
make


echo 
echo "1: Testing pgmEcho for invalid inputs"
./pgmEcho fakeTest fakeTest.pgm
echo -e "\n1 Result: Returned $?"
echo

echo "2: Testing pgmEcho for valid inputs"
./pgmEcho slice0a.pgm realTest.pgm
echo -e "\n2 Result: Returned $?"
rm realTest.pgm
echo

echo "3: Testing pgmComp for valid inputs"
./pgmComp slice0a.pgm slice0a.pgm
echo -e "\n3 Result: Returned $?"
echo

echo "4: Testing pgma2b"
./pgma2b slice0a.pgm slice0b.pgm
echo -e 
./pgmComp slice0a.pgm slice0b.pgm
echo -e "\n4 Result: Returned $?"
echo

echo "5: Testing pgmb2a"
./pgmb2a slice0b.pgm newSlice0a.pgm
echo -e 
./pgmComp slice0b.pgm newSlice0a.pgm
echo -e "\n5 Result: Returned $?"
echo

echo "6: Testing pgmComp for non-equivalent pgms"
./pgmComp slice0a.pgm notSlice0a.pgm
echo -e "\n6 Result: Returned $?"
echo

echo "7: Testing pgmComp for non-equivalent pgms"
./pgmComp slice0a.pgm slice0b.pgm
echo -e "\n7 Result: Returned $?"
echo

echo "8: Testing pgmReduce for reduction factor 4"
./pgmReduce baboon.ascii.pgm 4 reducedBaboon.ascii.pgm
echo -e "\n8 Result: Returned $?"
echo

echo "9: Testing pgmTile for tile factor 4"
./pgmTile baboon.ascii.pgm 4 "tiledBaboon.ascii.pgm_<row>_<column>.pgm"
echo -e "\n9 Result: Returned $?"
echo

echo "Running 'make clean'"
make clean
