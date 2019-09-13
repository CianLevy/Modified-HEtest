if [ "$#" -ne 1 ]; then
    echo "Error: Illegal number of parameters. Enter the name of the folder containing the test data."
    exit 1
fi
./../test-harness/debug/test-harness.out -s ../baseline/helib/server/debug/helib-server-main.out -c ../baseline/helib/client/debug/helib-client-main.out -t circuits/helib/$1/test.txt -d log