print("This file tests logical operation.")
for i in range(0, 100):
    if i>=80 and (i%5==0 or i%10==0):
        print("This number is bigger than 80 and multiples of 5: ")
        print(i)