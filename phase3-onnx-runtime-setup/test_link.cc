#include <onnxruntime_cxx_api.h>
#include <iostream>

int main() {
    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "test");
    std::cout << "ONNX Runtime linked successfully!" << std::endl;
    return 0;
}
