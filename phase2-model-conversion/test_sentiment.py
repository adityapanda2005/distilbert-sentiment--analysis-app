import onnxruntime as ort
from transformers import DistilBertTokenizer
import numpy as np

tokenizer = DistilBertTokenizer.from_pretrained(
    "distilbert-base-uncased-finetuned-sst-2-english")
session = ort.InferenceSession("distilbert_sentiment.onnx")

tests = [
    "This movie was absolutely wonderful!",
    "Terrible service, I want a refund.",
    "The weather is okay today."
]

for text in tests:
    inputs = tokenizer(text, return_tensors="np")
    outputs = session.run(None, {
        "input_ids": inputs["input_ids"],
        "attention_mask": inputs["attention_mask"]
    })
    logits = outputs[0][0]
    label = "POSITIVE" if logits[1] > logits[0] else "NEGATIVE"
    confidence = np.exp(logits) / np.exp(logits).sum()
    print(f"Input: {text}")
    print(f"Result: {label} ({confidence.max():.1%})")
    print()
