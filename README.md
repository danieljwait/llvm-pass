# LLVM Pass
LLVM pass that prints out the number of functions and basic blocks in a given program, on stderr

## Build

Ensure `clang` and `opt` version 15 are installed.

```bash
make
```
Builds the shared object in a build directory.

## Usage

To run the pass on a source code file called `program.c` do the following at the root of the repository:

```bash
clang-15 -emit-llvm -c program.c
```
Will generate the LLVM bitcode file `program.bc`

```bash
opt-15 -load build/CountingPass/libLLVMCountingPass.so \
  --counting-pass \
  -enable-new-pm=0 \
  program.bc >/dev/null
```
Will run the pass
