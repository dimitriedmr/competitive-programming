import math

def binExp (b,e):
  ans = 1
  while(e > 0):
    if(e % 2):
      ans = ans * b
    b = b * b
    e = e >> 1
    print("new base: " + str(b) + " new answer: " + str(ans))
  return ans


if __name__ == '__main__':
  stopCounter = 6
  with open("UVa11029LeadingAndTrailing.input") as f:
    content = f.readlines()
  numbers = []   
  print (content[0])
  tests = int(content[0])
  index = 1
  while(tests):
    b,e = [int(s) for s in content[index].split()]
    index = index + 1
    print(str(b) + "  " + str(e))
    power = pow(b,e)
    #stepPower = binExp(b,e)
    print(str(power))# + " " + str(stepPower))
    if(stopCounter < 1):
      break;
    stopCounter = stopCounter - 1;
