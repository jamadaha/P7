# Go gack to parent dir
cd ..;
# Make directory to install all the packages into
mkdir P7Requirements;
cd P7Requirements;
# Make sure all current packages are up to date
sudo apt update;

git clone https://gitlab.com/atorralba_planners/h2-preprocessor h2-preprocessor && cd h2-preprocessor && echo "Change ALLOW_64_BIT to true in h2-preprocessor Macros.cmake" && sleep 30 && mkdir -p builds/release32 && cd builds/release32 && cmake ../../ && cmake --build . && cd ../../../; 
# Install Catch2
git clone https://github.com/catchorg/Catch2.git Catch2 && cd Catch2 && cmake -Bbuild -H. -DBUILD_TESTING=OFF && sudo cmake --build build/ --target install && cd ..;
# Install Fast Downward
sudo apt install cmake g++ git make python3 && git clone https://github.com/aibasel/downward.git && cd downward && ./build.py && cd ..;
# Install VAL
sudo apt install g++ make flex bison && git clone https://github.com/KCL-Planning/VAL.git && cd VAL && git checkout a5565396007eee73ac36527fbf904142b3077c74 && make clean && sed -i 's/-Werror //g' Makefile && make && cd ..;
# Install Lab
sudo apt install python3-pip && pip install lab
# Install R
sudo apt install r-base r-base-dev
sudo apt install libudunits2-dev
sudo apt install libgdal-dev
sudo Rscript -e "install.packages(\"ggplot2\");"
sudo Rscript -e "install.packages(\"data.table\");"
sudo Rscript -e "install.packages(\"plyr\");"
sudo Rscript -e "install.packages(\"bigsnpr\");"
sudo Rscript -e "install.packages(\"ggpubr\");"
sudo Rscript -e "install.packages(\"ggpattern\");"
sudo Rscript -e "install.packages(\"reshape2\");"
# Download data repo
git clone https://github.com/jamadaha/P7_Data
