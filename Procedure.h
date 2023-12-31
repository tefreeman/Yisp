#pragma once
#include "Environment.h"
#include "Types.h"
#include "Parser.cpp"

using namespace types;

class Procedure
{
  private:
    List params;
    std::any body;
    Environment env;


  public:
    Procedure(std::any& params_, std::any& body_, Environment* env_) {
      params = toList(params_);
      body = body_;

     // Gives the ability to easily support set outside gobal scope
     env = Environment(env_);
    }

    std::any call(List args) {
    throwBadArgCount("procedure.call", args, params.size());
    
    //std::cout << "PROCEDURE:  " << stringifyOutput(args) << std::endl;


    // Add the arguments to the (called) environment
    Environment callEnv = Environment(&env);
    for (int i = 0; i < params.size(); i++) {
      Symbol param = toSymbol(params[i]);
      callEnv.define(param, args[i]);
    }
    return eval(body, callEnv);
    }



};

