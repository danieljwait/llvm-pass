#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/LegacyPassManager.h"

using namespace llvm;

namespace
{
  struct CountingPass : public FunctionPass
  {
    static char ID;
    CountingPass() : FunctionPass(ID) {}

    int funcs = 0;
    int bbs = 0;

    virtual bool runOnFunction(Function &F) override
    {
      funcs++;
      bbs += F.size();
      return false;
    }

    virtual bool doFinalization(Module &M) override
    {
      errs() << "The program has a total of ";
      errs() << funcs << " functions and ";
      errs() << bbs << " basic blocks.\n";
      return false;
    }
  };
}

char CountingPass::ID = 0;
static RegisterPass<CountingPass> X("counting-pass",
                                    "Count functions and basic blocks",
                                    false /* Only looks at CFG */,
                                    false /* Analysis Pass */);