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
- [ ] Read operations from files.

### Build and run:

Require `cmake`, `GNU make` and a C compiler.

```console
git clone https://github.com/mscode98/svm.git
cd svm
cmake .
make
./svm
```