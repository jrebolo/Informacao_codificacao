from matplotlib import pyplot as plt
def main():
  mean = []
  sample0 = []
  sample1 = []
  index = []
  with open("out.dat") as f:
    lines = f.readlines()
  for line in lines:
    i,m,s0,s1 = line.strip().split(' ')
    index.append(int(i))
    mean.append(int(m))
    sample0.append(int(s0)) 
    sample1.append(int(s1)) 
  
  plt.figure(0)
  plt.title("Mean Histogram")
  plt.bar(index,mean)
  plt.figure(1)
  plt.title("Histogram sample channel 0")
  plt.bar(index,sample0)
  plt.figure(2)
  plt.title("Histogram sample channel 1")
  plt.bar(index,sample1)
  plt.show()
if __name__ == "__main__":
  main()
