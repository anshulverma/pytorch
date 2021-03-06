#include <torch/script.h>

#include "op.h"

#include <cstddef>
#include <vector>

std::vector<torch::Tensor> custom_op(
    torch::Tensor tensor,
    double scalar,
    int64_t repeat) {
  std::vector<torch::Tensor> output;
  output.reserve(repeat);
  for (int64_t i = 0; i < repeat; ++i) {
    output.push_back(tensor * scalar);
  }
  return output;
}

static auto registry =
    torch::jit::RegisterOperators()
        // We parse the schema for the user.
        .op("custom::op", &custom_op)
        // User provided schema. Among other things, allows defaulting values,
        // because we cannot infer default values from the signature. It also
        // gives arguments meaningful names.
        .op("custom::op_with_defaults(Tensor tensor, float scalar = 1, int repeat = 1) -> Tensor[]",
            &custom_op);
