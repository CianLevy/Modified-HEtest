if [ "$#" -ne 1 ]; then
    echo "Error: Illegal number of parameters. Enter the name of the folder containing the test data."
    exit 1
fi
./../test-harness/debug/test-harness.out -s ../baseline/heaan/server/debug/heaan-server-main.out -c ../baseline/heaan/client/debug/heaan-client-main.out -t circuits/heaan/$1/test.txt -d log