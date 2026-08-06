# SYSTEM ARCHITECTURE AND DESIGN 
- The system follows a single-service, containerized architecture on Kubernetes, deployed as a confidential container
 and the wokload running inside a hardware sealed enclave and encrypted by the processor
- Also the design is minimal and it contain two main parts **one inference service plus one security helper (the SKR sidecar)**, rather than having a broad microservice system.As our goal is to This is a obvious choice the goal of the POC is to prove a security property (that data is only ever readable inside the enclave), not to build a large distributed application. Keeping the architecture small means the trust chain is easy to reason about, easy to demonstrate, and has a small surface area to secure.

# SYSTEM BLOCK DESIGN

```mermaid
flowchart LR
    Client["Client<br/>(encrypts input)"] --> Ingress
    Ingress --> Inf

    subgraph AKS["AKS Confidential Node Pool — AMD SEV-SNP"]
      subgraph Pod["Confidential Pod (encrypted memory)"]
        Inf["Inference Service<br/>DistilBERT"]
        SKR["SKR Sidecar"]
      end
    end

    SKR -->|1. attest| MAA["MAA<br/>(attestation)"]
    MAA -->|2. token| SKR
    SKR -->|3. token| AKV["Azure Key Vault<br/>(Secure Key Release)"]
    AKV -->|4. release key| SKR
    Inf -->|result| Client
```
# LINK BETWEEN ATTESTATION AND KEY RELEASE
```mermaid
sequenceDiagram
    participant C as Client
    participant P as SKR Sidecar (in pod)
    participant M as MAA
    participant K as Key Vault (SKR)
    participant I as Inference Service (in TEE)

    C->>P: Encrypted input (RSA-OAEP)
    P->>M: Send attestation evidence (SEV-SNP)
    M-->>P: Signed attestation token
    P->>K: Present token
    K-->>P: Release decryption key
    P->>I: Provide key
    I->>I: Decrypt inside TEE + run inference
    I-->>C: Sentiment result
```
