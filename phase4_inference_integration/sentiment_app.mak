CERTIFIER_ROOT=/home/aditya/certifier-framework-for-confidential-computing
ONNX_INC=/home/aditya/onnxruntime-linux-x64-1.18.1/include
ONNX_LIB=/home/aditya/onnxruntime-linux-x64-1.18.1/lib
SIMPLE_APP_DIR=/home/aditya/certifier-framework-for-confidential-computing/sample_apps/simple_app

CFLAGS = \
	-I. \
	-I$(CERTIFIER_ROOT)/include \
	-I$(ONNX_INC) \
	-I$(CERTIFIER_ROOT)/src/sev-snp/ \
	-I$(CERTIFIER_ROOT)/src/tpm2 \
	-O3 -g -Wall -std=c++17 \
	-Wno-unused-variable -D X64 \
	-Wno-deprecated-declarations \
	-DSIMPLE_APP -fPIC \
	-DNEW_API -Wno-strict-aliasing \
	-Wno-error

LDFLAGS = \
	-L$(ONNX_LIB) \
	-lonnxruntime \
	-Wl,-rpath,$(ONNX_LIB) \
	-lpthread -lssl -lcrypto -ldl \
	`pkg-config --cflags --libs protobuf` \
	-lgtest -lgflags

EXISTING_OBJS = \
	$(SIMPLE_APP_DIR)/certifier.pb.o \
	$(SIMPLE_APP_DIR)/certifier.o \
	$(SIMPLE_APP_DIR)/certifier_proofs.o \
	$(SIMPLE_APP_DIR)/support.o \
	$(SIMPLE_APP_DIR)/simulated_enclave.o \
	$(SIMPLE_APP_DIR)/application_enclave.o \
	$(SIMPLE_APP_DIR)/cc_helpers.o \
	$(SIMPLE_APP_DIR)/cc_useful.o \
	$(SIMPLE_APP_DIR)/tpm2.pb.o \
	$(SIMPLE_APP_DIR)/tpm2_lib.o \
	$(SIMPLE_APP_DIR)/openssl_help.o \
	$(SIMPLE_APP_DIR)/convert.o \
	$(SIMPLE_APP_DIR)/tpm2_support.o

# Only two new objects — policy_key is included inside sentiment_app.cc already
NEW_OBJS = \
	sentiment_app.o \
	sentiment_inference.o

all: sentiment_app.exe

sentiment_app.o: sentiment_app.cc sentiment_inference.h
	g++ $(CFLAGS) -c -o $@ sentiment_app.cc

sentiment_inference.o: sentiment_inference.cc sentiment_inference.h
	g++ $(CFLAGS) -c -o $@ sentiment_inference.cc

sentiment_app.exe: $(NEW_OBJS) $(EXISTING_OBJS)
	g++ -o $@ $(NEW_OBJS) $(EXISTING_OBJS) $(LDFLAGS)
	@echo "Build successful! sentiment_app.exe created."

clean:
	rm -rf sentiment_app.o sentiment_inference.o sentiment_app.exe
