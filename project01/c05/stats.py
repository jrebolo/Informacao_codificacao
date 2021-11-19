from matplotlib import pyplot as plt
def main():
  index    = []
  character = []
  with open("out.dat") as f:
    lines = f.readlines()
  for line in lines:
    i,c = line.strip().split(' ')
    character.append(int(c))
    index.append(i)
  
  plt.figure(0)
  plt.title("Characters Histogram")
  plt.bar(index,character)
  plt.show()
if __name__ == "__main__":
  main()
