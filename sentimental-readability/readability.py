import re


text = input("Text: ")

phrases = re.split(r"[.!?]", text)
words = text.split(" ")

words_without_punctuation = re.split(r"[.,!-;:?'\s]\s*", text)
letter = []
for word in words_without_punctuation:
    letter_in_word = list(word)
    for one_letter in letter_in_word:
        letter.append(one_letter)

S = (len(phrases) - 1) * (100 / len(words))
L = len(letter) * (100 / len(words))
if (0.0588 * L - 0.296 * S - 15.8) < 1:
    print("Before Grade 1")
elif (0.0588 * L - 0.296 * S - 15.8) >= 1 and (0.0588 * L - 0.296 * S - 15.8) < 16:
    print(f"Grade {round(0.0588 * L - 0.296 * S - 15.8)}")
else:
    print("Grade 16+")
