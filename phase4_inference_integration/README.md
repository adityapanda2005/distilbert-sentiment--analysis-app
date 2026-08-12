# Phase 4: Inference Integration Inside Enclave

This folder contains the separate source files, build configurations, execution scripts, and successful output logs for running the ONNX DistilBERT model securely inside a confidential computing enclave.

**Files Included:**
- `sentiment_inference.h` / `.cc`: ONNX Runtime inference logic.
- `sentiment_app.cc`: The main enclave application utilizing the inference code.
- `sentiment_app.mak`: The Makefile to compile the integration.
- `run_sentiment.sh`: The bash script to boot the Certifier Service, provision keys, and test the app.
- `sentiment-demo-output.txt`: The terminal output proving successful cryptographic attestation and POSITIVE sentiment inference.
