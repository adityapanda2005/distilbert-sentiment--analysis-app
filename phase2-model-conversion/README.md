## BUILDING THE distilBERT model (ML model)
- This **distilBERT model** does the sentiment analysis so it uses pytorch which is basically a python framework .
- so it conatins the python code which can't be used in c++ enclave so we have to convert it into the onnx format 
and whatever output is produced in pytorch it runs on onnx runtime.Because **.onnx** runtime is where c++ code can run it is acting as a bridge between the python code andc c++ enclave

## what it contains?
- `convert_model.py` — exports HuggingFace model to `distilbert_sentiment.onnx` + `.onnx.data`
- `test_sentiment.py` — verifies the exported model produces correct predictions
- `test_output.txt` — sample output from running the test

## FUTURE PHASES
- phase 3: onnx runtime c++ setup which is required so that enclave app can run this
- phase 4: enclave inference integration basically it will decrypt the input and run the inference and result will return back the client 
- phase 5: build client which will send the encrypted input to the enclave through secure channel
