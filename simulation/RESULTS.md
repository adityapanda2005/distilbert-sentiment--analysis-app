# SIMULATION RESULT- "CERTIFIER FRAMEWORK"

So, i have cretaed a opensource confidential computing by using **certifier framework** replacing the paid MAA + AKV services.
And i built the certifier server as a simpleserver which  helps me to create the trust chain which includes **attestation+ certification** flow succeds

## What works
- The Certifier Service (open-source attestation/policy server) starts.
- The app generates its attestation and sends evidence to the service.
- The proof verifies: `ValidateInternalEvidence: Proof verifies`.
- The app is certified: `Status: succeeded`

## what we mapped
- simulated enclave -> confidential VM
- attestation -> MAA(microsft azure)
- certification -> AKV key released

## SIMULATION MODEL ARCHITECTURE 
- Attestation succeeded means: the app proved it was genuine , it showed cryptographic evidence of exactly what code it is and that it's running in a real simulated encalve.
- Certification succeeded means: the Certifier Service checked that proof against the policy and approved it , basically it confirmed the app is trusted and it released the certificate.


## Full output
See `demo-output.txt` for the complete terminal log. it shows how it is working

## Note
The final app-to-app SSL secret exchange has a TLS handshake issue
(newer OpenSSL). In the simulated model it have two apps both need to prove its genuineness and then only it got certfied(certifier service)
instead like in my system diagram where only sealed enclave need to prove its genuiness and client only send the encrypted input. But the core trust chain flow worked basically the security part (core part) only the connection between two apps not bale to established.
