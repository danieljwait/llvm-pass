#include <map>
#include <iostream>
#include <fstream>
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/LegacyPassManager.h"

using namespace llvm;

namespace
{
  const char *data_file_name = "tmp.dat";

  struct CountingPass : public FunctionPass
  {
    static char ID;
    CountingPass() : FunctionPass(ID) {}

    std::map<int, int> instr_map;
    int funcs = 0;
    int bbs = 0;

    virtual bool runOnFunction(Function &F) override
    {
      // New function seen
      funcs++;

      for (auto const &B : F)
      {
        // Each new block in a function is a new basic block seen
        bbs++;

        // Update histogram with # instructions in basic block
        int num_instr = B.size();
        if (instr_map.count(num_instr))
          instr_map[num_instr]++;
        else
          instr_map[num_instr] = 1;
      }

      return false;
    }

    virtual bool doFinalization(Module &M) override
    {
      errs() << "The program has a total of "
             << funcs << " functions and "
             << bbs << " basic blocks.\n";

      // Write data to temp file
      std::ofstream file;
      file.open(data_file_name);
      for (auto const &i : instr_map)
        file << i.first << '\t' << i.second << '\n';
      file.close();

      // Produce histogram
      system("gnuplot script.plt > instr_per_bb.pdf");

      // Remove temp file
      remove(data_file_name);

      return false;
    }
  };
}

char CountingPass::ID = 0;
static RegisterPass<CountingPass> X("counting-pass",
                                    "Count functions and basic blocks",
                                    false /* Only looks at CFG */,
                                    false /* Analysis Pass */);