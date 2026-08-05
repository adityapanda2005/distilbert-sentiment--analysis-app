# confidential-computing-POC-DEMO-
# **OBJECTIVE**-TO build a sentiment analysis app inside a confidential TEE setup
SO, the proof of concept of running this sentiment analysis app inside a confidential Trusted Execution enviorment which will decrypts your memory region inside a hardware sealed enclave so that it will never exposed to the software layer like hypervisor, OS and cloud operator.

# **PROBLEM STATEMENT**
In stanadard cloud when data leaves it get exposed to the softwrae layer during computation , so while the data is in use inside the memory it is in derypted way so it get privileged for other to acess it, But we can close this gap by building confidential computing that's the main reason why we are building this. A small sentiment analysis app can help to solve without exposing the data to others.

# **STACK USED FOR THE INTIAL DEMO**
- we  can use Azure Confidential Containers (CoCo) on AMD SEV-SNP as it wrap whole container basically the chip will encrypts the whole VM memory with per VM key per pod.And it is useful from other stack as no single doorway ECALL/OCALL required , no c++ code like in intel SGX
- Also we can add a Azure ML Non-Confidential Baseline as it will be a simple ML (scikit-leran + Fast API ) it is lightweight app doing same work like what we  are building called sentiment app. so, the main purpose to use this to do comparision on the basis of latency and cost against the stack we are using and it will help to decide or it will give a good vision though because of building this app required cost and time and it should be worthy .(OPTIONAL)

# Documents - what it includes:
- one plan for demo POC
- second HDL DESIGN DOC
- third for IMPLEMENTATION DOC

# status
currently doing research for this and reviewing the plan for the app.
