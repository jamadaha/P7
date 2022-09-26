# P7
## Requirements
### Catch2
Catch2 is used for testing.
In order to install run the following

<code>
git clone https://github.com/catchorg/Catch2.git <br>
cd Catch2 <br>
cmake -Bbuild -H. -DBUILD_TESTING=OFF <br>
sudo cmake --build build/ --target install <br>
</code>

This downloads the library, builds it, and installs it to path