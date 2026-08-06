#   Why we are byilding this and how it can be useful?
In standard cloud the data get exposed to software layers like OS , hypervisor and cloud operator and it happens because data used to be in encyption only two states
- first in if the data is in rest
- second the data is in transit
- the main flaw comes when the data is in use(data is present in the form of plaintext readable format) generally when the computation happen it should be in decryption state so that computation can happen due to which it get exposed to outer operators.
  To  close this gap we have idea to build confidential computing so that it will create a hardware based trusted execution enviorment(TEE) , A sealed encalve room but still in decryption state where we can still do computation but inside the enclave which is encrypts by a chip and walls off so no outside operators can access it . Also it provide a cryptographic proof (Attestation) it is done by service called microsoft azure attestaion(MAA)which checks the  code running inside the enclave it should be same  and then realease the token and a remote party can verify it against the proof before releasing any key or data inside into it.
  So, for this reason this app called sentiment analysis inside TEE container setp could be useful..

  # KEY OBJECTIVES OF BUILDING THIS APP
  - **confidential processing**: inpute data is decrypted and processed in encalve only so it is not readable by a os , hypervisor orcloud operator
  - **Attestaion gated-key reease**: the decryption key only relesaed after getting valid token afterthe attestaion proves it genuiness in which he code is running.
  - **verifable failure**: if it found the tampered token and then it will not release the key for decryption.

  # VALUE FOR POC
- Proves it actually works	Instead of assuming confidential computing protects our data, we see it working on a real app — with proof that the infrastructure genuinely can't read the data.
- Gives us a template to reuse	Once we get this flow working once, we can copy the same setup for any future app that handles sensitive data. We solve it now, reuse it later.
- this confidential computing is useful in many sectors like pharma where patients record are confidential , in financial services where , in defence & government where the document is confidential , ML models whose weights get exposed , and in Saas platforms

  # STACK USED FOR THIS DEMO APP: **Azure Confidential Containers (CoCo) on AMD SEV-SNP**
  **it includes two main parts**:
  -  AMD SEV-SNP is the hardware layer. It is an AMD processor feature that encrypts an entire virtual machine's memory with a key held inside the chip, and blocks the host OS and hypervisor from reading or tampering with it. This is the hardware that makes the enclave possible.
  -  Azure confidential container basically it is the platform layer,  It runs each container inside its own lightweight, hardware-protected VM on an AKS confidential node pool. In other words, it lets us take an ordinary container and run it inside a sealed, SEV-SNP-protected environment.
Both leads to give a TEE setup(whole container): so that we can drop our app and its memory gets protected and without changing the app code

**FEATURES**:
- Fastest path of working demo we can containeraize whole python app and can run as it is and dont need to rewrite the whole app inside the enclave, and in the alternate process (SGX) requires splitting the app into trusted and untrusted parts, also required single doorway ECALL/OCALL with a custom boundary and C++ enclave code which will be more complex for intail part
- The flow — attestation → key release → in-TEE decryption → inference — maps directly onto a clear, step-by-step demo that a reviewer can follow and verify.theflow workks end-t-end correctly
- Easiest way of integration because it wrap the whole container  and it required minimal changes , fast way to adapt
- It's  strong design  microsoft azure attestation(MAA) and key management  (vault key services) due to which key is released against the proof only and

# HIGH LEVEL ARCHITECTURE 
the data is only ever readable inside the enclave, and the key that unlocks it is handed over only after the enclave proves it is genuine and it contains several components
**COMPONENTS**:
- **Client**:encrypts its input before sending, so the data is protected on the way in and can only be opened inside the enclave.
- **confidential pod**: the sealed workload, running in its own hardware-protected VM (AMD SEV-SNP) so its memory is encrypted and unreadable from outside. It holds two parts: **Inference service** (this is your actual app: the DistilBERT model that reads the input and returns the sentiment result. Without it, there's nothing doing the work. Obviously required).SKR sidecar (a helper that proves the pod is genuine and fetches the key).
- **MAA (Microsoft Azure Attestation)**: the independent verifier. It checks the enclave's hardware proof and, if valid, issues a signed token , which indicates it is genuine and protected enclave
- **AKV (Azure Key Vault)**: the key holder. It releases the decryption key only when shown a valid attestation token. if it is not verified against proof then no key released
**END-TO-END FLOW**:
- **Client encrypts** the input and sends it in through the ingress.
- **Pod attests** on startup, the SKR sidecar sends the enclave's hardware proof to MAA.
- **MAA verifies** the proof and returns a signed token.
- **AKV releases** the key only because that token is valid.
- **Decrypt** inside the TEE — the input is decrypted (RSA-OAEP) inside the enclave, never outside it.
- **Inference**  DistilBERT runs on the decrypted input.
- **Result** returned to the client.
# COMPLETE CHAIN STRUCTURE FOR THE FLOW
The chain is what we demonstrate:
- hardware seals the room → attestation proves the room is genuine → the key is released only against that proof → the data is processed safely inside. Break any link (e.g. tamper with the workload) and the chain stops before the data is ever exposed.
- this flow of chain will be followed for the app by passing through the all the layers so that data will be not exposed to the outer operators.
  
# SCOPE:
**IN SCOPE**:
- A working sentiment-analysis app running inside a confidential container.
- The full trust chain: attestation → key release → in-TEE decryption → inference.
- positive and neagative demonstartion: for positive works end to end: the enclave is genuine → attestation passes → the key is released → the data is decrypted inside the enclave → the model produces a correct sentiment result this proof only the it runs correctly while in neagative it tamper with the workload or run a modified/unexpected version. Now attestation fails → the key is not released → the data can never be decrypted → inference cannot run. Through this classification we can getv concrete idea of how it is protecting for complete proof
  **out scope**:
  - Non-confidential baseline, this is used for comparison against the stack we are using to do compare with cost and speed so that we have idea with proper number the app we are building with the  prefered stack is worthy of using
  - this can be add later stage of production oce after we made the app for more adavanced .
 
# SUCCESS CRITERIA
-  Data stays sealed: encrypted input is decrypted and processed only inside the TEE; it is never readable by the host OS, hypervisor, or cloud operator.
- Key is gated by proof: Azure Key Vault releases the decryption key only when attestation confirms a genuine, unmodified enclave.
- Failure is provable: in the negative test, a tampered or unexpected workload fails attestation, no key is released, and inference cannot run. This is the key proof that the protection is real, not just an app on confidential hardware.
- The app still works:  a valid end-to-end request returns a correct sentiment result.

# OUTCOME AT THE END 
- we can build our DEMO app
- HLD design doc
- implementation doc
  


  
  

