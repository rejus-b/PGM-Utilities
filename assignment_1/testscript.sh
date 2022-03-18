echo
echo
echo

echo "Running 'make'"
make


echo 
echo "1: Testing pgmEcho for invalid inputs"
./pgmEcho fakeTest fakeTest.pgm
echo "1 Result: Returned $?"
echo

echo "2: Testing pgmEcho for valid inputs"
./pgmEcho slice0a.pgm realTest.pgm
echo "2 Result: Returned $?"
rm realTest.pgm
echo

echo "3: Testing pgmComp for valid inputs"
./pgmComp slice0a.pgm slice0a.pgm
echo "3 Result: Returned $?"
echo

echo "4: Testing pgma2b"
./pgma2b slice0a.pgm slice0b.pgm
echo "4 Result: Returned $?"
rm slice0b.pgm
echo

echo "5: Testing pgmComp for non-equivalent pgms"
./pgmComp slice0a.pgm fakeSlice.pgm
echo "5 Result: Returned $?"
echo