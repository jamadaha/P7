# P7
## Requirements
### Catch2
Catch2 is used for testing.
In order to install run the following

<code>
git clone https://github.com/catchorg/Catch2.git &&
cd Catch2 &&
cmake -Bbuild -H. -DBUILD_TESTING=OFF &&
sudo cmake --build build/ --target install
</code>

This downloads the library, builds it, and installs it to path