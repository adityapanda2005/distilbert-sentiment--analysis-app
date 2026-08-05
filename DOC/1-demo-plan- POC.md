#   Why we are byilding this and how it can be useful?
In standard cloud the data get exposed to software layers like OS , hypervisor and cloud operator and it happens because data used to be in encyption only two states
- first in if the data is in rest
- second the data is in transit
  the main flaw comes when the data is in use(data is present in the form of plaintext readable format) generally when the computation happen it should be in decryption state so that computation can happen due to which it get exposed to outer operators.
  To  close this gap we have idea to build confidential computing so that it will create a hardware based trusted execution enviorment(TEE) , A sealed encalve room but still in decryption state where we can still do computation but inside the enclave which is encrypts by a chip and walls off so no outside operators can access it . Also it provide a cryptographic proof (Attestation) it is done by service called microsoft azure attestaion(MAA)which checks the  code running inside the enclave it should be same  and then realease the token and a remote party can verify it against the proof before releasing any key or data inside into it.
  So, for this reason this app called sentiment analysis inside TEE container setp could be useful..

  # KEY OBJECTIVES OF BUILDING THIS APP
  - **confidential processing**: inpute data is decrypted and processed in encalve only so it is not readable by a os , hypervisor orcloud operator
  - **Attestaion gated-key reease**: the decryption key only relesaed after getting valid token afterthe attestaion proves it genuiness in which he code is running.
  - **verifable failure**: if it found the tampered token and then it will not release the key for decryption.

  # VALUE FOR POC
- Proves it actually works	Instead of assuming confidential computing protects our data, we see it working on a real app — with proof that the infrastructure genuinely can't read the data.
- Gives us a template to reuse	Once we get this flow working once, we can copy the same setup for any future app that handles sensitive data. We solve it now, reuse it later.
- Helps with compliance	For rules that require sensitive data to stay private (health, finance, etc.), we can point to a working system as real evidence — not just a promise on paper.
- Teaches the team	The team learns how the pieces fit together (the secure enclave, the attestation check, the key release) on a low-risk demo, before using them on anything important.

