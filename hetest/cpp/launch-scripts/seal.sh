if [ "$#" -ne 1 ]; then
    echo "Error: Illegal number of parameters. Enter the name of the folder containing the test data."
    exit 1
fi
./../test-harness/debug/test-harness.out -s ../baseline/seal/server/debug/seal-server-main.out -c ../baseline/seal/client/debug/seal-client-main.out -t circuits/seal/$1/test.txt -d log