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
    List body;
    Environment* env;

  public:
    Procedure(std::any& params_, std::any& body_, Environment* env_) {

      if(params_.type() != typeid(List)) {
        params = List(1, params_);
      } else {
        params = std::any_cast<List>(params_);
      }

      if (body_.type() != typeid(List)) {
        body = List(1, body_);
      } else {
        body = std::any_cast<List>(body_);
      };

     env = env_;
    }

    std::any call(List args) {
    if (params.size() != args.size()) {
      throw std::runtime_error("Incorrect number of arguments passed to procedure");
    }
    Environment tempEnv = Environment(env);

    for (int i = 0; i < params.size(); i++) {
      Symbol param = std::any_cast<Symbol>(params[i]);
      tempEnv.define(param, args[i]);
    }
    return eval(body, tempEnv);
    //~Procedure();
    }



};

