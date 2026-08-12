from transformers import DistilBertTokenizer
tok = DistilBertTokenizer.from_pretrained("distilbert-base-uncased-finetuned-sst-2-english")
tok.save_vocabulary(".")
print("vocab.txt saved")
