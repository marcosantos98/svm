# svm - smoll virtual machine

Virtual machine that executes the given instructions.

### Todo:
- [x] Require empty stack.
- [ ] All operations:
  - [ ] Operand comparation (less than, less than equal, equal);
  - [ ] Math (plus, minus)
  - [x] Jump instructions (Jump not equal and jump);
  - [x] Stack manipulation (push, dup, drop);
  - [x] Print current, dump the stack;
- [x] Read operations from files.

### Build and run:

Require `cmake`, `GNU make` and a C compiler.

The current program prints the number from 0 to 10 to the console.

```console
git clone https://github.com/mscode98/svm.git
cd svm
cmake .
make
./svm <input.svm>
```

Run tests:
```console
./test.sh
```