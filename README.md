
# How to run
First, run this command : python extrainst.py example.txt.
this will generate two files, namely blocks.txt and example.txt. blocks.txt contains contains the block related data. order.txt contains the edge related info.
then run this command : g++ modified.cpp -o output
finally, run this command : ./output
it will show all the possible trigrams on the console.


# modified.cpp
this file contains the C++ code which builds the CFG,does DFS and generates the trigrams.

# extrainst.py
this file contains the python code that extracts data from the dot file. here, for the sake of example the contents of dot file is inside example.txt


