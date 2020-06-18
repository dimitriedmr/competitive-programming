import math

base = 123456
exponent = range(47,48)

def binExp (b,e):
  ans = 1
  while(e > 0):
    if(e % 2):
      ans = ans * b
    b = b * b
    e = e >> 1
    print("new base: " + str(b) + " new answer: " + str(ans))
  return ans

for ex in exponent:
  power = pow(base,ex)
  
  stepPower = binExp(base,ex)
  print(str(power) + " " + str(stepPower))

if __name__ == '__main__':
  with open("UVa11029LeadingAndTrailing.input") as f:
    content = f.readlines()
