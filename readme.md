# svm - smoll virtual machine

Virtual machine that executes the given instructions.

### Build and run:

Require `cmake`, `GNU make` and a C compiler.

The current program prints the number from 0 to 10 to the console.

```console
git clone https://github.com/mscode98/svm.git
cd svm
mkdir build && cd build
cmake ..
make
./svm <input.svm>
```

Run tests:
```console
./test.sh
```