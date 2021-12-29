from matplotlib import pyplot as plt
def main():
  res1 = [0 for i in range(65536)]
  res2 = [0 for i in range(65536)]
  with open("hist.data") as f:
    lines = f.readlines()
  for line in lines:
    r1,r2 = line.strip().split(' ')
    r1 = int(r1)
    r2 = int(r2)
    res1[r1+32767] += 1
    res2[r2+32767] += 1
  x = [(i-32767) for i in range(65536)]
  #plt.figure(0)
  #plt.title("Histogram residual of ch1")
  #plt.bar(x,res1)
  plt.figure(1)
  plt.title("Histogram residual of channel 2")
  plt.bar(x,res2)
  plt.show()
if __name__ == "__main__":
  main()

