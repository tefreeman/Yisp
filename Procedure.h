#pragma once
#include "Environment.h"
#include "Types.h"
#include <stdexcept>
#include "Parser.cpp"

using namespace types;

class Procedure
{
  private:
    List params;
    std::any body;
    Environment* env;


  public:
    Procedure(std::any& params_, std::any& body_, Environment* env_) {
      
      if(!isList(params_)) {
        this->params = List(1, params_);
      } else {
        this->params = toList(params_);
      }

      if (!isList(body_)) {
        this->body = List(1, body_);
      } else {
        this->body = toList(body_);
      };

     // Gives the ability to easily support set outside gobal scope
     env = new Environment(env_);
    }

    std::any call(List args) {
    throwBadArgCount("procedure.call", args, params.size());

    // Prevents accidently modifying scope then calling procedure without correct params
    Environment tempEnv(env);
    for (int i = 0; i < params.size(); i++) {
      Symbol param = toSymbol(params[i]);
      env->define(param, args[i]);
    }
    return eval(body, tempEnv);
    }



};

