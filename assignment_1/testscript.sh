echo
echo
echo

echo "Running 'make'"
make

add_colour()
{
    RETURN=$1
    EXPECTED=$2
    TESTNUM=$3

    GREEN="\e[32m"
    RED="\e[31m"
    NC="\033[0m"

    if [ $1 == $2 ]
    then
        echo -e "\n$3 Result: Returned ${GREEN}$1${NC}"
    else
        echo -e "\n$3 Result: Returned ${RED}$1${NC}"
    fi
}

echo 
echo "1: Testing pgmEcho for invalid inputs"
./pgmEcho images/fakeTest images/fakeTest.pgm
add_colour $? 2 1
echo

echo "2: Testing pgmEcho for valid inputs"
./pgmEcho images/slice0a.pgm images/realTest.pgm
add_colour $? 0 2
rm images/realTest.pgm
echo

echo "3: Testing pgmComp for valid inputs"
./pgmComp images/slice0a.pgm images/slice0a.pgm
add_colour $? 0 3
echo

echo "4: Testing pgma2b"
./pgma2b images/slice0a.pgm images/slice0b.pgm
echo
./pgmComp images/slice0a.pgm images/slice0b.pgm
add_colour $? 0 4
echo

echo "5: Testing pgmb2a"
./pgmb2a images/slice0b.pgm images/newSlice0a.pgm
echo -e 
./pgmComp images/slice0b.pgm images/newSlice0a.pgm
add_colour $? 0 5
echo

echo "6: Testing pgmComp for non-equivalent pgms"
./pgmComp images/slice0a.pgm images/notSlice0a.pgm
add_colour $? 0 6
echo

echo "7: Testing pgmComp for non-equivalent pgms"
./pgmComp images/slice0a.pgm images/slice0b.pgm
add_colour $? 0 7
echo

echo "8: Testing pgmReduce for reduction factor 4"
./pgmReduce images/baboon.ascii.pgm 4 images/reducedBaboon.ascii.pgm
add_colour $? 0 8
rm images/reducedBaboon.ascii.pgm
echo

echo "9: Testing pgmTile for tile factor 4"
./pgmTile images/baboon.ascii.pgm 4 "images/tiledBaboon.ascii.pgm_<row>_<column>.pgm"
add_colour $? 0 9
echo

echo "10: Testing pgmAssemble for canvas 512x512 with tiles of 216x216"
./pgmAssemble images/Vernon.pgm 512 512 0 0 images/tiledBaboon.ascii.pgm_0_0.pgm 128 0 images/tiledBaboon.ascii.pgm_1_0.pgm 256 0 images/tiledBaboon.ascii.pgm_2_0.pgm 384 0 images/tiledBaboon.ascii.pgm_3_0.pgm 0 128 images/tiledBaboon.ascii.pgm_0_1.pgm 128 128 images/tiledBaboon.ascii.pgm_1_1.pgm 256 128 images/tiledBaboon.ascii.pgm_2_1.pgm 384 128 images/tiledBaboon.ascii.pgm_3_1.pgm 0 256 images/tiledBaboon.ascii.pgm_0_2.pgm 128 256 images/tiledBaboon.ascii.pgm_1_2.pgm 256 256 images/tiledBaboon.ascii.pgm_2_2.pgm 384 256 images/tiledBaboon.ascii.pgm_3_2.pgm 0 384 images/tiledBaboon.ascii.pgm_0_3.pgm 128 384 images/tiledBaboon.ascii.pgm_1_3.pgm 256 384 images/tiledBaboon.ascii.pgm_2_3.pgm 384 384 images/tiledBaboon.ascii.pgm_3_3.pgm
add_colour $? 0 10
rm images/tiledBaboon.*
rm images/Vernon.pgm
echo

echo "Running 'make clean'"
make clean
