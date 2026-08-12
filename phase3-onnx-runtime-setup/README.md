# ONNX runtime setup
- onnx runtime c++ setup which is required so that enclave app can run this , it is completed
- onnx runtime successfully linked that you can see in the output

# what it contains?
- export_vocab.py : exports the DistilBERT tokenizer's vocabulary to 
  `vocab.txt`, used later for in-C++ tokenization (since the enclave has 
  no access to the Python `transformers` library)
- test_link.cc : a minimal sanity-check program that initializes an 
  ONNX Runtime environment (`Ort::Env`) to confirm the C++ headers and 
  shared library are correctly installed and linked
- test_output.txt :  captured output from running the compiled test, 
  confirming a successful link
