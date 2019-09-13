##  Documentation Overview
This document provides an overview of how to use this modified version of the
HEtest framework for homomorphic evaluation of circuits using the SEAL, HElib
and HEAAN libraries. For further information regarding the structure of HEtest
and how to use HEtest please see the documentation available in the HEtest
repository: https://github.com/y4n9squared/HEtest

## Structural Overview
The client and server for each library is implemented using a modified version
of the original binary plaintext client and server provided in HEtest. The
HEtest binary server is implemented by inheriting some basic functions from a
generic server implemented in hetest/cpp/baseline/common/baseline.h.
Consequently, the integer, SEAL, HElib, and HEAAN servers are all derived from
this generic server. Source code for the client and server for each library can
be found in hetest/cpp/baseline/<library-name>

## Building the framework
Before compiling the framework the paths to all the libraries must be set in
the SConscript files (SConscript files tell scons how to build the framework)
for both the servers and clients. The relevant SConscript file for each 
client/server can be found in the same folder as the client/server code. Both 
the CPPPATH and LIBPATH must be changed in all SConscript files. The paths are
currently set to "/home/cian/Libraries/<library name>". Assuming the libraries
are all installed in the same directory, the easiest solution to correctly 
setting the library paths is to find and replace all instances of 
"/home/cian/Libraries/" in the framework with the correct path.

After the paths have been set, the framework can be compiled by running the 
"build.sh" script found in the "hetest" folder. Compilation will likely fail on
the first few attempts as the order of dependencies means that all the required
libraries cannot be compiled at once. Simply run the script until there are no 
longer any errors.

## Generating Circuits
The first step involved in using the framework is circuit generation. To
generate a circuit using the circuit generation tools provided in the
framework, create a folder to contain the test data (circuit description,
inputs, cryptographic parameters) and create a file called "config.txt" in the
folder. Circuits are generated based on the parameters contained in
"config.txt". The following example shows the format of "config.txt":

test_type = RANDOM
num_circuits = 1
num_inputs = 1
num_levels = 5
K = 80
L = 1
D = 24
W = 10
B = 10
generate = True

An explanation of the parameters in the config can be found in the readme in
hetest/python/circuit_generation/int_circuit/README.txt. The 'B' parameter
controls the bound on input values and constants used throughout the generated
circuit. The modified circuit generation tool for integer circuits with bounded
inputs can be found under
hetest/python/circuit_generation/int_circuit/ibm_generate.py
To generate a circuit based on a config.txt file, run ibm_generate.py and pass
the location of the folder containing config.txt. To generate a circuit based
on the example config.txt above enter: python2 ibm_generate.py TEST_1

## Evaluating a Circuit
To evaluate a circuit, copy the folder containing the circuit data (as
generated using the generation tool) to the relevant folder for the selected
library under hetest/cpp/launch-scripts/circuits/. Manually enter the
cryptographic parameters in the txt in the "key" folder inside the circuit
folder. (See the readmes for each library in the folders in
hetest/cpp/launch-scripts/circuits/ for further information regarding the
parameters in the key txt.) 
To launch the test harness and evaluate the circuit, run the relevant script in
hetest/cpp/launch-scripts/ and pass the name of the circuit folder. For
example: to evaluate "TEST_1" using helib enter: ./helib.sh TEST_1. A
successfully completed test should output six txt files in the folder
containing the scripts. The expected output should be: results.txt, state.txt
and four other txts which log the communication between the client and server.
The "results.txt" file contains the result of circuit evaluation and the
recorded times for the cryptographic operations and circuit evaluation. Note:
the test harness has been rewritten to ensure that communication delays are not
recorded in the profiling results. 
