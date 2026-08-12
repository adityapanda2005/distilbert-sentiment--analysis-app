#include "sentiment_inference.h"
#include <onnxruntime_c_api.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <string>
#include <cmath>

std::string run_sentiment(const std::string& model_path,
                          const std::string& text) {
  const OrtApi* ort = OrtGetApiBase()->GetApi(ORT_API_VERSION);
  OrtEnv* env = nullptr;
  ort->CreateEnv(ORT_LOGGING_LEVEL_WARNING, "sentiment", &env);
  OrtSessionOptions* opts = nullptr;
  ort->CreateSessionOptions(&opts);
  OrtSession* session = nullptr;
  OrtStatus* status = ort->CreateSession(env, model_path.c_str(), opts, &session);
  if (status != nullptr) {
    printf("ONNX error: %s\n", ort->GetErrorMessage(status));
    ort->ReleaseStatus(status);
    ort->ReleaseSessionOptions(opts);
    ort->ReleaseEnv(env);
    return "ERROR";
  }
  std::vector<int64_t> tokens = SimpleTokenizer::tokenize(text);
  int64_t seq_len = (int64_t)tokens.size();
  std::vector<int64_t> attn(seq_len, 1);
  int64_t shape[2] = {1, seq_len};
  OrtMemoryInfo* mem_info = nullptr;
  ort->CreateCpuMemoryInfo(OrtArenaAllocator, OrtMemTypeDefault, &mem_info);
  OrtValue* input_ids_tensor = nullptr;
  OrtValue* attn_mask_tensor = nullptr;
  ort->CreateTensorWithDataAsOrtValue(mem_info, tokens.data(),
      seq_len * sizeof(int64_t), shape, 2,
      ONNX_TENSOR_ELEMENT_DATA_TYPE_INT64, &input_ids_tensor);
  ort->CreateTensorWithDataAsOrtValue(mem_info, attn.data(),
      seq_len * sizeof(int64_t), shape, 2,
      ONNX_TENSOR_ELEMENT_DATA_TYPE_INT64, &attn_mask_tensor);
  const char* input_names[]  = {"input_ids", "attention_mask"};
  const char* output_names[] = {"logits"};
  OrtValue* inputs[]  = {input_ids_tensor, attn_mask_tensor};
  OrtValue* outputs[] = {nullptr};
  status = ort->Run(session, nullptr, input_names, inputs, 2,
                    output_names, 1, outputs);
  std::string result = "UNKNOWN";
  if (status != nullptr) {
    printf("Inference error: %s\n", ort->GetErrorMessage(status));
    ort->ReleaseStatus(status);
  } else {
    float* logits = nullptr;
    ort->GetTensorMutableData(outputs[0], (void**)&logits);
    float neg = logits[0];
    float pos = logits[1];
    float exp_neg = expf(neg);
    float exp_pos = expf(pos);
    if (pos > neg) {
      float conf = exp_pos / (exp_neg + exp_pos) * 100.0f;
      printf("Sentiment: POSITIVE (%.1f%% confidence)\n", conf);
      result = "POSITIVE";
    } else {
      float conf = exp_neg / (exp_neg + exp_pos) * 100.0f;
      printf("Sentiment: NEGATIVE (%.1f%% confidence)\n", conf);
      result = "NEGATIVE";
    }
    ort->ReleaseValue(outputs[0]);
  }
  ort->ReleaseValue(input_ids_tensor);
  ort->ReleaseValue(attn_mask_tensor);
  ort->ReleaseMemoryInfo(mem_info);
  ort->ReleaseSession(session);
  ort->ReleaseSessionOptions(opts);
  ort->ReleaseEnv(env);
  return result;
}
