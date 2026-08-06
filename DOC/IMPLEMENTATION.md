# IMPLEMENTATION
- Build the application — the DistilBERT sentiment inference service; confirm it runs inference correctly on sample text locally.
- Provision confidential infrastructure — AKS cluster + confidential node pool (SEV-SNP) + CoCo/Kata → forms the hardware-sealed environment.
- Containerize — build the image and store it in the registry.
- Deploy the confidential pod — deploy the stored image onto the confidential node pool; it runs inside a sealed utility VM.
- Add attestation + key release — the SKR sidecar attests to MAA, gets the signed token, and releases the decryption key from Key Vault.
- TEE decryption + inference — inside the sealed pod, the input is decrypted using the released key, and the DistilBERT model runs inference to produce the sentiment result (positive/negative).
- Wire the end-to-end client flow — client encrypts input → pod attests → key released → decrypt in TEE → inference → result returned.

# TESTING AND VALIDATION
- Positive test: a valid workload attests successfully, the key is released, and inference returns a correct result.
- Negative test (critical): a tampered or unexpected workload fails attestation, the key is not released, and inference cannot run. This is the core proof that the protection is real.
- Isolation check: confirm the data cannot be read from outside the enclave like oS , hypervisor and cloud operator 

# CHECKING COST AND TIME 
- we can add  **Azure ML Non-Confidential Baseline** it is  a basic ML model that we can deploy using scikit-learn using FAST API serving endpoint to measure latency and cost against the stack we are using so that we can compare with the numeric numbers

