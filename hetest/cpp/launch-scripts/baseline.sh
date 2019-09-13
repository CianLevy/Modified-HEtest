if [ "$#" -ne 1 ]; then
    echo "Error: Illegal number of parameters. Enter the name of the folder containing the test data."
    exit 1
fi
./../test-harness/debug/test-harness.out -s ../baseline/integer/server/debug/integer-baseline-main.out -c ../baseline/integer/client/debug/integer-client.out -t circuits/base/$1/test.txt -d log