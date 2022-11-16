# Go gack to parent dir
cd ..;
# Make directory to install all the packages into
mkdir P7Requirements;
cd P7Requirements;
# Make sure all current packages are up to date
sudo apt update;

# Install Catch2
git clone https://github.com/catchorg/Catch2.git Catch2 && cd Catch2 && cmake -Bbuild -H. -DBUILD_TESTING=OFF && sudo cmake --build build/ --target install && cd ..;
# Install Fast Downward
sudo apt install cmake g++ git make python3 && git clone https://github.com/aibasel/downward.git && cd downward && ./build.py;
# Install VAL
sudo apt install g++ make flex bison && git clone https://github.com/KCL-Planning/VAL.git && cd VAL && git checkout a5565396007eee73ac36527fbf904142b3077c74 && make clean && sed -i 's/-Werror //g' Makefile && make;
# Install Lab
sudo apt install python3-pip && pip install lab
# Download data repo
cd .. && cd.. && git clone https://github.com/jamadaha/P7_Data